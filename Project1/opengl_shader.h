#pragma once

#include "common.h"
#include "opengl_common.h"
#include <map>

namespace planet {
	class OpenGLShader : public OpenGLObject {
	private:
		GLenum type;

	public:
		OpenGLShader(GLenum type);
		GLenum getType() const;
		bool compile(string const& file);
		~OpenGLShader();
	};

	class OpenGLShaderProgram : public OpenGLObject {
	private:
		map<GLenum, OpenGLShader*> shaders;

	public:
		OpenGLShaderProgram();
		void include(OpenGLShader* shader);
		bool link();
		~OpenGLShaderProgram();
	};
}