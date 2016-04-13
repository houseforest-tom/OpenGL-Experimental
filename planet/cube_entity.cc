#include "cube_entity.h"
#include "model_component.h"

namespace planet {
	CubeEntity::CubeEntity() {
		auto model = (ModelComponent*)addComponent("model", new ModelComponent());
		mesh = new Mesh();

		Vertex* vertices = new Vertex[8];
		vertices[0].position = { -0.5, 0.5, 0.5 };
		vertices[1].position = { 0.5, 0.5, 0.5 };
		vertices[2].position = { 0.5, -0.5, 0.5 };
		vertices[3].position = { -0.5, -0.5, 0.5 };
		vertices[4].position = { 0.5, 0.5, -0.5 };
		vertices[5].position = { -0.5, 0.5, -0.5 };
		vertices[6].position = { -0.5, -0.5, -0.5 };
		vertices[7].position = { 0.5, -0.5, -0.5 };

		for (int i = 0; i < 8; ++i) {
			vertices[i].color = {
				((float)rand() / RAND_MAX),
				((float)rand() / RAND_MAX),
				((float)rand() / RAND_MAX)
			};
		}

		u16* indices = new u16[36] {
			0, 1, 2, // Front
			2, 3, 0,
			1, 4, 7, // Right
			7, 2, 1,
			4, 5, 6, // Back
			6, 7, 4,
			5, 0, 3, // Left
			3, 6, 5,
			5, 4, 1, // Top
			1, 0, 5,
			3, 2, 7, // Bottom
			7, 6, 3
		};

		mesh->updateVertexBuffer(
			vertices,
			8,
			GL_STATIC_DRAW
		);

		mesh->updateIndexBuffer(
			indices,
			36,
			GL_STATIC_DRAW
		);

		model->mesh = mesh;
	}

	CubeEntity::~CubeEntity() {
		delete mesh;
	}
}