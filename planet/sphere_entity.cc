#include "sphere_entity.h"
#include "model_component.h"
#include "deform_component.h"

namespace planet {

	vec3 SphereEntity::getUnitSpherePoint(float theta, float phi) {
		return { sin(theta) * cos(phi), cos(theta), sin(theta) * sin(phi) };
	}

	SphereEntity::SphereEntity(OpenGLShaderProgram* shader, ViewProjComponent const* viewproj)
		: Entity("Sphere") {

		mesh = new Mesh();
		
		constexpr u32 n = 100;
		constexpr u32 nsqr = n * n;
		constexpr float PI = 3.14159265f;
		constexpr float latitudeStep = PI / n;
		constexpr float longitudeStep = latitudeStep + latitudeStep;
		u32 latitudeNo = 0, longitudeNo = 0, normalNo = 0, indexNo = 0;

		constexpr u32 vertexCount = 4 * nsqr;
		constexpr u32 indexCount = (nsqr - 1) * 6;
		vec3 normals [vertexCount];
		u16* indices = new u16[indexCount];

		for (latitudeNo = 0; latitudeNo < n; ++latitudeNo) {
			float theta = latitudeNo * latitudeStep;

			for (longitudeNo = 0; longitudeNo < n; ++longitudeNo) {
				float phi = longitudeNo * longitudeStep;

				/*
					2--1	1: (theta,  phi)
					|\ |	2: (theta,  phi+)
					| \|	3: (theta+, phi+)
					3--4	4: (theta+, phi)
				*/

				u32 normalBase = normalNo;
				normals[normalNo++] = getUnitSpherePoint(theta, phi); 
				normals[normalNo++] = getUnitSpherePoint(theta, phi + longitudeStep); 
				normals[normalNo++] = getUnitSpherePoint(theta + latitudeStep, phi + longitudeStep);
				normals[normalNo++] = getUnitSpherePoint(theta + latitudeStep, phi);

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

		components["orientation"] = new OrientationComponent();
		components["deform"] = new DeformComponent((OrientationComponent*)components["orientation"]);
		components["model"] = new ModelComponent(mesh, shader, (OrientationComponent*)components["orientation"], viewproj);
	}

	SphereEntity::~SphereEntity() {
		delete mesh;
	}
}