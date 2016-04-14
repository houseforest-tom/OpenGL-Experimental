#pragma once

#include "entity.h"

namespace planet {

	Entity::Entity(string const& type) 
		: type(type) {}

	void Entity::update(float dt) {
		for (auto& component : components) {
			component.second->update(dt);
		}
	}

	void Entity::render() {
		for (auto& component : components) {
			component.second->render();
		}
	}

	map<string, Component*> Entity::getTypedComponents(string const& type) {
		map<string, Component*> result;
		for (auto const& component : components) {
			if (component.second->type == type) {
				result.insert(component);
			}
		}
		return result;
	}

	Entity::~Entity() {
		for (auto& component : components) {
			delete component.second;
		}
	}
}