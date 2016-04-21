#include "viewproj_component.h"

namespace planet {

	ViewProjComponent::ViewProjComponent(mat4 const &projection, OrientationComponent* orientation)
		: orientation(orientation), projection(projection) {}

	void ViewProjComponent::update(float dt) {
		viewProjMatrix = projection * glm::lookAt(orientation->position, orientation->position + forward, up);
	}
}
