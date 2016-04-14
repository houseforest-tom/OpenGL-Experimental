#pragma once

#include "orientation_component.h"

namespace planet {
	class DeformComponent : public Component {
	private:
		OrientationComponent* orientation;

	public:
		DeformComponent(OrientationComponent* orientation);
		void update(float dt);
	};
}