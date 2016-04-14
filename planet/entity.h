#pragma once

#include "common.h"
#include "component.h"
#include <map>

namespace planet {

	struct Scene;

	// Entity base class.
	struct Entity {

		// Entity type name.
		string type;

		// Attached components.
		map<string, Component*> components;

		// Initializes the entity.
		Entity(string const& type);

		// Update all components.
		virtual void update(float dt);

		// Render all components.
		virtual void render();

		// Returns all components of a given type.
		map<string, Component*> getTypedComponents(string const& type);

		// Delete attached components.
		virtual ~Entity();
	};
}