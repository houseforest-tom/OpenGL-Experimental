#include "camera_entity.h"

namespace planet {
	CameraEntity::CameraEntity(GLFWwindow* window)
	: Entity("Camera") {

		int windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		components["orientation"] = new OrientationComponent();
		components["viewproj"] = new ViewProjComponent(glm::perspective(45.0f, (float)windowWidth / windowHeight, 100.0f, 0.01f), (OrientationComponent*)components["orientation"]);
	}
}