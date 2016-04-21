#pragma once

#include "entity.h"

namespace planet {
	class Scene {
	private:
		// Maximum number of entities.
		static const u32 MAX_ENTITIES = (1 << 20);

		// Entities by name.
		Entity *entities[MAX_ENTITIES];

		// Number of entities.
		u32 entityCount = 0;

		// Highest assigned entity id.
		u32 highestID = 0;
		
		// Return the highest id in use.
		void updateHighestID();

		// Return the next free entity id.
		bool findAvailableID(u32 &available);

	public:
		// Create a new scene.
		Scene() = default;

		// Update all entities.
		void update(float dt);

		// Render all entities.
		void render();

		// Adds an entity to the scene.
		void addEntity(Entity *entity);

		// Deletes an entity from the scene.
		void deleteEntity(u32 id);

		// Returns the number of entities.
		inline u32 getEntityCount() const { return entityCount; }

		// Returns the entity with the given id.
		inline Entity *getEntity(u32 id) { return entities[id]; }

		// Delete all entities.
		~Scene();
	};
}