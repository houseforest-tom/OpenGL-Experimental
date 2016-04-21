#include "sphere_entity.h"
#include "model_component.h"
#include "deform_component.h"

namespace planet {

	vec3 SphereEntity::getUnitSpherePoint(float theta, float phi) {
		return { sin(theta) * cos(phi), cos(theta), sin(theta) * sin(phi) };
	}

	float getTheta(u32 latitudeNo, u32 longitudeNo, const u32 tesselation) {
		return latitudeNo * 3.14159265f / tesselation;
	}

	float getPhi(u32 latitudeNo, u32 longitudeNo, const u32 tesselation) {
		return 2 * longitudeNo * 3.14159265f / tesselation;
	}

	SphereEntity::SphereEntity(OpenGLShaderProgram const *shader, ViewProjComponent const *viewproj) {
		mesh = new Mesh();
		orientation = new OrientationComponent();
		deform = new DeformComponent(orientation);
		model = new ModelComponent(mesh, shader, orientation, viewproj);
		
		constexpr u32 n = 32;
		constexpr u32 nsqr = n * n;
		u32 latitudeNo = 0, longitudeNo = 0, normalNo = 0, indexNo = 0;

		constexpr u32 vertexCount = 4 * nsqr;
		constexpr u32 indexCount = (nsqr - 1) * 6;
		vec3 normals [vertexCount];
		u16* indices = new u16[indexCount];

		for (latitudeNo = 0; latitudeNo < n; ++latitudeNo) {
			for (longitudeNo = 0; longitudeNo < n; ++longitudeNo) {

				/*
					2--1	1: (theta,  phi)
					|\ |	2: (theta,  phi+)
					| \|	3: (theta+, phi+)
					3--4	4: (theta+, phi)
				*/

				u32 normalBase = normalNo;
				normals[normalNo++] = getUnitSpherePoint(getTheta(latitudeNo,     longitudeNo, n), getPhi(latitudeNo, longitudeNo,     n));
				normals[normalNo++] = getUnitSpherePoint(getTheta(latitudeNo,     longitudeNo, n), getPhi(latitudeNo, longitudeNo + 1, n));
				normals[normalNo++] = getUnitSpherePoint(getTheta(latitudeNo + 1, longitudeNo, n), getPhi(latitudeNo, longitudeNo + 1, n));
				normals[normalNo++] = getUnitSpherePoint(getTheta(latitudeNo + 1, longitudeNo, n), getPhi(latitudeNo, longitudeNo,     n));

				// Close the top of the sphere.
				if (latitudeNo == 0) { 
					indices[indexNo++] = normalBase;
					indices[indexNo++] = normalBase + 2;
					indices[indexNo++] = normalBase + 3;
				}

				// Close the bottom the sphere.
				else if (latitudeNo == n - 1) { 
					indices[indexNo++] = normalBase + 2;
					indices[indexNo++] = normalBase;
					indices[indexNo++] = normalBase + 1;
				}
				else
				{
					indices[indexNo++] = normalBase;
					indices[indexNo++] = normalBase + 1;
					indices[indexNo++] = normalBase + 3;
					indices[indexNo++] = normalBase + 1;
					indices[indexNo++] = normalBase + 2;
					indices[indexNo++] = normalBase + 3;
				}
			}
		}

		Vertex* vertices = new Vertex[vertexCount];
		for (u32 i = 0; i < vertexCount; ++i) {
			vertices[i].position = normals[i];

			vertices[i].color = {
				i / (float)vertexCount,
				0,
				1.0f - i / (float)vertexCount
			};
		}

		mesh->updateVertexBuffer(
			vertices,
			vertexCount,
			GL_STATIC_DRAW
		);

		mesh->updateIndexBuffer(
			indices,
			indexCount,
			GL_STATIC_DRAW
		);

		logMessage("Generated sphere mesh of tesselation " + to_string(n));
		logMessage("Vertices: " + to_string(vertexCount) + " (" + to_string(vertexCount * sizeof(Vertex) / (1 << 10)) + " kB)");
		logMessage("Indices:  " + to_string(indexCount)  + " (" + to_string(indexCount  * sizeof(u16)    / (1 << 10)) + " kB)");
	}

	void SphereEntity::update(float dt) {
		model->update(dt);
		deform->update(dt);
	}

	void SphereEntity::render() {
		model->render();
	}

	SphereEntity::~SphereEntity() {
		delete model;
		delete deform;
		delete orientation;
		delete mesh;
	}
}