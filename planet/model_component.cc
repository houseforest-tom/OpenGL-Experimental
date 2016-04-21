#include "model_component.h"

namespace planet {

	ModelComponent::ModelComponent(
		Mesh* mesh,
		OpenGLShaderProgram const* shader,
		OrientationComponent const* orientation,
		ViewProjComponent const* viewproj)
		:
		shader(shader),
		orientation(orientation),
		viewproj(viewproj),
		mesh(mesh) 
	{}

	void ModelComponent::update(float dt) {
		modelMatrix =
			translate(orientation->position)
			* rotate(orientation->rotation.x, vec3 { 1,0,0 })
			* rotate(orientation->rotation.y, vec3 { 0,1,0 })
			* rotate(orientation->rotation.z, vec3 { 0,0,1 })
			* glm::scale(orientation->scale);
	}

	void ModelComponent::render() {
		static mat4 mvp;

		mvp = viewproj->getMatrix() * modelMatrix;
		glUseProgram(shader->id);
		glUniformMatrix4fv(
			glGetUniformLocation(shader->id, "modelViewProj"),
			1,
			GL_FALSE,
			&mvp[0][0]
		);
		mesh->render();
	}
}