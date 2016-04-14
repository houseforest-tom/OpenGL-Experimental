#pragma once

#include "common.h"
#include "component.h"
#include "mesh.h"
#include "opengl_shader.h"
#include "orientation_component.h"
#include "viewproj_component.h"

namespace planet {
	
	// Component that stores all information needed to display a model on screen.
	class ModelComponent : public Component {
	private:
		// Shader program to use.
		OpenGLShaderProgram const* shader = nullptr;

		// Orientation in space.
		OrientationComponent const* orientation = nullptr;

		// View projection provider used for rendering.
		ViewProjComponent const* viewproj = nullptr;

	public:
		// Mesh to render.
		Mesh* mesh = nullptr;

		// Model matrix passed to shader.
		mat4 modelMatrix;

		ModelComponent(
			Mesh* mesh, 
			OpenGLShaderProgram const* shader, 
			OrientationComponent const* orientation, 
			ViewProjComponent const* viewproj);

		void update(float dt);

		void render();
	};
}