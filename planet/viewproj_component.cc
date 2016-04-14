#include "viewproj_component.h"

planet::ViewProjComponent::ViewProjComponent(mat4 const& projection, OrientationComponent* orientation)
	: planet::Component("Camera"), projection(projection), orientation(orientation) {
}

void planet::ViewProjComponent::update(float dt) {
	viewProjection = projection * glm::lookAt(orientation->position, orientation->position + forward, up);
}
