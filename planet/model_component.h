#pragma once

#include "common.h"
#include "component.h"
#include "mesh.h"

namespace planet {
	
	// Component that stores all information needed to display a model on screen.
	struct ModelComponent : public Component {
		Mesh* mesh;
		vec3 position;
		vec3 rotation;
		vec3 scale;
		mat4 modelMatrix;

		void update(float dt);
		void render();
	};
}