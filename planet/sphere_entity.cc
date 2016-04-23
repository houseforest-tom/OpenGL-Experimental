#include "sphere_entity.h"
#include "model_component.h"
#include "deform_component.h"

namespace planet {

	vec3 SphereEntity::getUnitSpherePoint(float theta, float phi) {
		return { sin(theta) * cos(phi), cos(theta), sin(theta) * sin(phi) };
	}

	float SphereEntity::getTheta(u16 latitude) {
		return latitude * 3.14159265f / latitudeTesselation;
	}

	float SphereEntity::getPhi(u16 longitude) {
		return 2 * longitude * 3.14159265f / longitudeTesselation;
	}

	float SphereEntity::random(float min, float max) {
		return min + rand() / (float)RAND_MAX * (max - min);
	}

	vec3 SphereEntity::randomColor() {
		return { random(), random(), random() };
	}

	float SphereEntity::getHeightmapEntry(u16 latitude, u16 longitude) {
		return heightmap[latitude + longitude * latitudeTesselation];
	}

	void SphereEntity::setHeightmapEntry(u16 latitude, u16 longitude, float value) {
		heightmap[latitude + longitude * latitudeTesselation] = value;
	}

	SphereEntity::SphereEntity(
		u16 latitudeTesselation,
		u16 longitudeTesselation,
		float radius,
		float maxDistortion,
		OpenGLShaderProgram const *shader,
		ViewProjComponent const *viewproj)
	: latitudeTesselation(latitudeTesselation),
	  longitudeTesselation(longitudeTesselation) {

		// Generate heightmap.
		heightmap = (float *)malloc(latitudeTesselation * longitudeTesselation * sizeof(float));
		for (u16 lon = 0; lon < longitudeTesselation; ++lon) {
			for (u16 lat = 0; lat < latitudeTesselation; ++lat) {
				setHeightmapEntry(lat, lon, random(1.0f, 1.1f));
			}
		}

		mesh        = new Mesh();
		orientation = new OrientationComponent();
		deform      = new DeformComponent(orientation);
		model       = new ModelComponent(mesh, shader, orientation, viewproj);
		
		const u16 vertexCount = 4 * latitudeTesselation * longitudeTesselation;
		Vertex* vertices = new Vertex[vertexCount];
		u16 vertexID = 0;

		const u32 indexCount = (latitudeTesselation * longitudeTesselation - 1) * 6;
		u16* indices = new u16[indexCount];
		u32 indexID = 0;

		u32 lat0, lat1, lon0, lon1;
		float height00, height01, height10, height11;

		for (lat0 = 0; lat0 < latitudeTesselation; ++lat0) {
			for (lon0 = 0; lon0 < longitudeTesselation; ++lon0) {

				lat1  = (lat0  + 1) % latitudeTesselation;
				lon1 = (lon0 + 1) % longitudeTesselation;

				/*
					4--1	1: (lat1, lon1)
					|\ |	2: (lat0, lon1)
					| \|	3: (lat0, lon0)
					3--2	4: (lat1, lon0)
				*/

				height00 = getHeightmapEntry(lat0, lon0);
				height01 = getHeightmapEntry(lat0, lon1);
				height10 = getHeightmapEntry(lat1, lon0);
				height11 = getHeightmapEntry(lat1, lon1);

				u16 baseVertexID = vertexID;

				vertices[vertexID++].position = height11 * getUnitSpherePoint(getTheta(lat0 + 1), getPhi(lon0 + 1));
				vertices[vertexID++].position = height01 * getUnitSpherePoint(getTheta(lat0),     getPhi(lon0 + 1));
				vertices[vertexID++].position = height00 * getUnitSpherePoint(getTheta(lat0),     getPhi(lon0));
				vertices[vertexID++].position = height10 * getUnitSpherePoint(getTheta(lat0 + 1), getPhi(lon0));

				for(u16 vid = baseVertexID; vid < baseVertexID + 4; ++vid) {
					float averageHeight = (height00 + height01 + height10 + height11) / 4.0f;
					vertices[vid].color = vec3((averageHeight - 1.0f) / 0.1f);
				};

				// Close the top of the sphere.
				if (lat0 == 0) {
					indices[indexID++] = baseVertexID;
					indices[indexID++] = baseVertexID + 2;
					indices[indexID++] = baseVertexID + 3;
				}

				// Close the bottom the sphere.
				else if (lat0 == latitudeTesselation - 1) {
					indices[indexID++] = baseVertexID + 2;
					indices[indexID++] = baseVertexID;
					indices[indexID++] = baseVertexID + 1;
				}
				else
				{
					indices[indexID++] = baseVertexID;
					indices[indexID++] = baseVertexID + 1;
					indices[indexID++] = baseVertexID + 3;
					indices[indexID++] = baseVertexID + 1;
					indices[indexID++] = baseVertexID + 2;
					indices[indexID++] = baseVertexID + 3;
				}
			}
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
		free(heightmap);
		delete model;
		delete deform;
		delete orientation;
		delete mesh;
	}
}