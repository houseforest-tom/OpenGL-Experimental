#pragma once

#include "entity.h"

namespace planet {
	struct Scene {

		// Entities by name.
		map<string, Entity*> entities;

		// Update all entities.
		virtual void update(float dt);

		// Render all entities.
		virtual void render();

		// Returns all entities of a given type.
		map<string, Entity*> getTypedEntities(string const& type);

		// Delete all entities.
		virtual ~Scene();
	};
}