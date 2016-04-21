#include "scene.h"


namespace planet {

	void Scene::update(float dt) {
		for (u32 id = 0; id <= highestID; ++id) {
			if (entities[id] != nullptr) {
				entities[id]->update(dt);
			}
		}
	}

	void Scene::render() {
		for (u32 id = 0; id <= highestID; ++id) {
			if (entities[id] != nullptr) {
				entities[id]->render();
			}
		}
	}

	void Scene::updateHighestID() {
		if (entityCount > 0) {
		    // Highest id must be between the current entity count and the previous maximum.
			for (u32 id = highestID - 1; id >= entityCount - 1; --id) {
				if (entities[id] != nullptr) {
					highestID = id;
				}
			}
		}
		else {
			highestID = -1;
		}
	}

	bool Scene::findAvailableID(u32 &available) {
		if (entityCount == MAX_ENTITIES) {
			return false;
		}

		if (entityCount == 0) {
			available = 0;
			return true;
		}

		for (u32 id = 0; id <= highestID; ++id) {
			if (entities[id] == nullptr) {
				available = id; // Use free id in the middle.
				return true;
			}
		}

		// Use id directly after the current max.
		available = ++highestID;
		return true;
	}

	void Scene::addEntity(Entity *entity) {
		u32 id;
		if (findAvailableID(id)) {
			entities[id] = entity;
			++entityCount;
		}
		else {
			logMessage("Max. number of entities reached.", Loglevel::error);
		}
	}

	void Scene::deleteEntity(u32 id) {
		delete entities[id];
		entities[id] = nullptr;
		--entityCount;

		if (id == highestID) {
			// Deleted entity had highest id.
			updateHighestID();
		}
	}

	Scene::~Scene() {
		if(entityCount > 0){
			u32 max = highestID;
			for (u32 id = 0; id <= max; ++id) {
				if (entities[id] != nullptr) {
					deleteEntity(id);
				}
			}
		}
	}
}