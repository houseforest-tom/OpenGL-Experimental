#include "camera_entity.h"

namespace planet {
	CameraEntity::CameraEntity(GLFWwindow* window) {
		int windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		orientation = new OrientationComponent();
		viewproj = new ViewProjComponent(glm::perspective(45.0f, (float)windowWidth / windowHeight, 100.0f, 0.01f), orientation);
	}

	void CameraEntity::update(float dt) {
		viewproj->update(dt);
	}
	
	CameraEntity::~CameraEntity() {
		delete viewproj;
		delete orientation;
	}
}