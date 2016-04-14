#pragma once

#include "entity.h"
#include "viewproj_component.h"

namespace planet {
	class CameraEntity : public Entity {
	public:
		CameraEntity(GLFWwindow* window);

		~CameraEntity() = default;
	};
}