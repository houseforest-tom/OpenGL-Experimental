#include "model_component.h"
#include <glm/gtx/transform.hpp>

namespace planet {

	void ModelComponent::update(float dt) {
		modelMatrix =
			translate(position)
			* rotate(rotation.x, vec3 { 1,0,0 })
			* rotate(rotation.y, vec3 { 0,1,0 })
			* rotate(rotation.z, vec3 { 0,0,1 })
			* glm::scale(scale);
	}
	
	void ModelComponent::render() {
		if (mesh != nullptr) {
			mesh->render();
		}
	}
}