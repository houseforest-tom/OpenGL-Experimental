#pragma once

#include "common.h"
#include "component.h"

namespace planet {

	// Entity base class.
	class Entity {
	private:
		// Maximum number of components allowed per entity.
		static constexpr u8 MAX_COMPONENTS = 16;

		// Handles to components attached to the entity.
		struct {
			string name;
			Component* ptr;
		} components[MAX_COMPONENTS] = {};
		
		// Number of components in use.
		u8 componentCount = 0;

	public:
		Entity() = default;

		// Returns a component by name.
		inline Component* getComponent(string const& name) {
			for (u8 i = 0; i < componentCount; ++i) {
				if (components[i].name == name) {
					return components[i].ptr;
				}
			}
			return nullptr;
		}

		// Adds a new component to the entity.
		inline Component* addComponent(string const& name, Component* component) {
			if (componentCount < MAX_COMPONENTS) {
				components[componentCount].name = name; 
				components[componentCount].ptr = component;
				++componentCount;
				return component;
			}
			return nullptr;
		}

		virtual void update(float dt);

		virtual void render();

		// Delete attached components.
		~Entity();
	};
}