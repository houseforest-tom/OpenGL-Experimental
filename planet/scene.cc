#include "scene.h"


namespace planet {

	void Scene::update(float dt) {
		for (auto& entity : entities) {
			entity.second->update(dt);
		}
	}

	void Scene::render() {
		for (auto& entity : entities) {
			entity.second->render();
		}
	}

	map<string, Entity*> Scene::getTypedEntities(string const& type) {
		map<string, Entity*> result;
		for (auto const& entity : entities) {
			if (entity.second->type == type) {
				result.insert(entity);
			}
		}
		return result;
	}

	Scene::~Scene() {
		for (auto& entity : entities) {
			delete entity.second;
		}
	}
}