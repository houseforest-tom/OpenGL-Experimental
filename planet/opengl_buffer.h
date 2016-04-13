#pragma once

#include "opengl_common.h"

namespace planet {
	class OpenGLBuffer : public OpenGLObject {
	public:
		OpenGLBuffer();
		~OpenGLBuffer();
	};

	class OpenGLVertexArray : public OpenGLObject {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
	};
}