#pragma once
#include "common.h"

namespace planet {

	struct Entity;

	// Component base class, stores data.
	struct Component {

		// Component type name.
		string type;
		
		// Initialize the component.
		Component(string const& type);

		// Update hook.
		virtual void update(float dt) {};
		
		// Render hook.
		virtual void render() {};

		// Default dtor.
		virtual ~Component() = default;
	};
}