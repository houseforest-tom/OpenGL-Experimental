#include "deform_component.h"

namespace planet {

	DeformComponent::DeformComponent(OrientationComponent* orientation)
		:orientation(orientation) {}

	void DeformComponent::update(float dt) {
		static float accu = 0.0f;
		orientation->rotation.y += dt;
		orientation->rotation.x -= dt;
		orientation->scale.y = 0.5 + 0.5f * abs(cos(accu += dt));
	}
}


