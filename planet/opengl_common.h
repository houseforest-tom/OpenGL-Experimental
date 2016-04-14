#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace planet {

	// Base class for OpenGL objects.
	struct OpenGLObject {
		GLuint id;
	};
}