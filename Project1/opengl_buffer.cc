#include "opengl_buffer.h"

namespace planet {

	OpenGLBuffer::OpenGLBuffer() {
		glGenBuffers(1, &id);
	}

	OpenGLBuffer::~OpenGLBuffer() {
		glDeleteBuffers(1, &id);
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &id);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &id);
	}
}