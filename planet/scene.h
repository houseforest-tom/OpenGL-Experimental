#pragma once

#include "entity.h"

namespace planet {
	class Scene {
	private:
		// Maximum number of entities allowed.
		static constexpr u16 MAX_ENTITIES = 1000;

		// Entities populating the scene.
		struct {
			string name;
			Entity* ptr;
		} entities[MAX_ENTITIES] = {};

		// Entities in use.
		u16 entityCount = 0;

	public:
		// Returns an entity by name.
		inline Entity* getEntity(string const& name) {
			for (u8 i = 0; i < entityCount; ++i) {
				if (entities[i].name == name) {
					return entities[i].ptr;
				}
			}
			return nullptr;
		}

		// Adds a new entity to the scene.
		inline Entity* addEntity(string const& name, Entity* entity) {
			if (entityCount < MAX_ENTITIES) {
				entities[entityCount].name = name;
				entities[entityCount].ptr = entity;
				++entityCount;
				return entity;
			}
			return nullptr;
		}

		// Update all entities.
		virtual void update(float dt);

		// Render all entities.
		virtual void render();

		// Delete all entities.
		virtual ~Scene();
	};
}