#pragma once

namespace planet {

	// Component base class, stores data.
	struct Component {
		Component() = default;
		virtual void update(float dt) {};
		virtual void render() {};
		virtual ~Component() = default;
	};
}