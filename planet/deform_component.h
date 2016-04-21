#pragma once

#include "orientation_component.h"

namespace planet {
	class DeformComponent : public Component {
	private:
		// Orientation component to apply the deformation to.
		OrientationComponent *orientation;
	
	public:
		DeformComponent(OrientationComponent *orientation);

		void update(float dt);
	};
}