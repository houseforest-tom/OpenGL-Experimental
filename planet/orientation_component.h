#pragma once

#include "component.h"

namespace planet {
	struct OrientationComponent : public Component {

		// Translation on X, Y and Z axes.
		vec3 position = { 0,0,0 };

		// Rotation around X, Y and Z axes in degrees.
		vec3 rotation = { 0,0,0 };

		// Scale factor along X, Y and Z axes.
		vec3 scale = { 1,1,1 };
	};
}