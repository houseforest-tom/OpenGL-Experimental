#include "opengl_shader.h"
#include <fstream>

namespace planet {
	OpenGLShader::OpenGLShader(GLenum type)
		:type(type) {
		id = glCreateShader(type);
	}

	GLenum OpenGLShader::getType() const {
		return type;
	}

	bool OpenGLShader::compile(string const& file) {
		// Open shader file.
		string code;
		ifstream filestream(file);
		if (!filestream.is_open()) {
			logMessage("Failed to open shader file: " + file, Loglevel::error);
			return false;
		}
		else {
			// Read code.
			string line;
			while (getline(filestream, line)) code += "\n" + line;
			filestream.close();

			// Compile source.
			auto sourcePtr = code.c_str();
			glShaderSource(id, 1, &sourcePtr, nullptr);
			glCompileShader(id);

			// Check result.
			GLint compileStatus, infoLen;
			glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLen);
			if (compileStatus == GL_FALSE) {
				logMessage("Failed to compile shader file: " + file, Loglevel::error);
				if (infoLen > 0) {
					GLchar* buf = new GLchar[infoLen];
					glGetShaderInfoLog(id, infoLen, nullptr, buf);
					logMessage("\nGLSL compiler output:\n" + string(buf, infoLen), Loglevel::error);
					delete[] buf;
				}
				return false;
			}
			else {
				logMessage("Successfully compiled shader file: " + file);
				return true;
			}
		}
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteShader(id);
	}

	OpenGLShaderProgram::OpenGLShaderProgram() {
		id = glCreateProgram();
	}

	void OpenGLShaderProgram::include(OpenGLShader* shader) {
		shaders[shader->getType()] = shader;
	}

	bool OpenGLShaderProgram::link() {
		for (const auto& shader : shaders) {
			glAttachShader(id, shader.second->id);
		}
		
		// Link program.
		glLinkProgram(id);

		// Check result.
		GLint linkStatus;
		GLint infoLen;
		glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLen);

		if (linkStatus == GL_FALSE) {
			logMessage("Failed to link shader program.", Loglevel::error);
			if (infoLen > 0) {
				GLchar* buf = new GLchar[infoLen];
				glGetProgramInfoLog(id, infoLen, nullptr, buf);
				logMessage("\nGLSL linker output:\n" + string(buf, infoLen), Loglevel::error);
				delete[] buf;
			}
			return false;
		}
		else {
			logMessage("Successfully linked shader program.");
			return true;
		}
	}

	OpenGLShaderProgram::~OpenGLShaderProgram() {
		for (const auto& shader : shaders) {
			glDetachShader(id, shader.second->id);
		}
		glDeleteProgram(id);
	}
}