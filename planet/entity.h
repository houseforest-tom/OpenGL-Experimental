#pragma once

#include "common.h"
#include "component.h"
#include <map>

namespace planet {

	// Entity base class.
	struct Entity {

		// Entity type name.
		u32 id;

		virtual void update(float dt) {}
		virtual void render() {}
		virtual ~Entity() {}
	};
}