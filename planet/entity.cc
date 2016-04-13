#pragma once

#include "entity.h"

namespace planet {

	void Entity::update(float dt) {
		for (u8 i = 0; i < componentCount; ++i) {
			components[i].ptr->update(dt);
		}
	}

	void Entity::render() {
		for (u8 i = 0; i < componentCount; ++i) {
			components[i].ptr->render();
		}
	}

	Entity::~Entity() {
		for (u8 i = componentCount - 1; i >= 0; --i) {
			delete components[i].ptr;
			--componentCount;
		}
	}
}