#pragma once

#include "entity.h"
#include "viewproj_component.h"

namespace planet {
	class CameraEntity : public Entity {
	private:
		OrientationComponent *orientation;
		ViewProjComponent    *viewproj;

	public:
		CameraEntity(GLFWwindow *window);

		virtual void update(float dt) override;
		virtual ~CameraEntity();

		inline OrientationComponent *getOrientation() { return orientation; }
		inline ViewProjComponent    *getViewProjection() { return viewproj; }
	};
}