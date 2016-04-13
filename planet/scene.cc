#include "scene.h"


namespace planet {
	
	void Scene::update(float dt) {
		for (u16 i=0; i<entityCount; ++i){
			entities[i].ptr->update(dt);
		}
	}

	void Scene::render() {
		for (u16 i = 0; i<entityCount; ++i) {
			entities[i].ptr->render();
		}
	}

	Scene::~Scene() {
		for (u16 i = entityCount - 1; i >= 0; --i) {
			delete entities[i].ptr;
			--entityCount;
		}
	}
}