#include "mesh.h"

namespace planet {
	Mesh::Mesh()
		:vertices(nullptr),
		vertexCount(0),
		indices(nullptr),
		indexCount(0) {

		// Generate & bind vertex array.
		vao = new OpenGLVertexArray();
		glBindVertexArray(vao->id);

		// Generate vertex buffer.
		vbo = new OpenGLBuffer();
		glBindBuffer(GL_ARRAY_BUFFER, vbo->id);

		// Enable vertex attributes.
		for (int attrib = 0; attrib < 4; ++attrib) {
			glEnableVertexAttribArray(attrib);
		}

		// Specify attribute locations inside buffer.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)(0 * sizeof(vec3)));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)(1 * sizeof(vec3)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)(2 * sizeof(vec3)));
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)(3 * sizeof(vec3)));

		// Generate index buffer.
		ibo = new OpenGLBuffer();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->id);

		// Unbind vertex array.
		glBindVertexArray(0);
	}

	void Mesh::updateVertexBuffer(Vertex* vertices, u16 count, GLenum usage) {
		glBindVertexArray(vao->id);

		// Delete old vertex data.
		if (this->vertices != nullptr) {
			delete[] this->vertices;
			this->vertices = nullptr;
			this->vertexCount = 0;
		}

		// Buffer new vertex data.
		if (vertices != nullptr && count > 0) {
			this->vertices = vertices;
			this->vertexCount = count;
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), vertices, usage);
		}

		glBindVertexArray(0);
	}

	void Mesh::updateIndexBuffer(u16* indices, u16 count, GLenum usage) {
		glBindVertexArray(vao->id);

		// Delete old index data.
		if (this->indices != nullptr) {
			delete[] this->indices;
			this->indices = nullptr;
			this->indexCount = 0;
		}

		// Buffer new index data.
		if (indices != nullptr && count > 0) {
			this->indices = indices;
			this->indexCount = count;
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u16), indices, usage);
		}

		glBindVertexArray(0);
	}

	Mesh::~Mesh() {
		glBindVertexArray(vao->id);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		delete ibo;
		delete vbo;
		delete vao;

		if (vertices != nullptr) delete[] vertices;
		if (indices != nullptr)  delete[] indices;
	}
}