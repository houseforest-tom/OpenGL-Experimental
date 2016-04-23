#include "input.h"

namespace planet {

	Input::Keys  Input::keys;
	Input::Mouse Input::mouse;

	void Input::install(GLFWwindow *window) {
		glfwSetKeyCallback(window, &Input::onKeyEvent);
		glfwSetCursorPosCallback(window, &Input::onMouseMoveEvent);
		glfwSetMouseButtonCallback(window, &Input::onMouseButtonEvent);
		glfwSetScrollCallback(window, &Input::onMouseScrollEvent);
	}

	void Input::update(float dt) {
		for (u16 key = 0; key < Keys::KEY_COUNT; ++key) {
			if (keys.down[key]) {
				keys.durations[key] += dt;
			}
		}
	}

	void Input::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
		u16 k = (u16)key - Keys::KEY_LO;

		if (insideRange(k, Keys::KEY_LO, Keys::KEY_HI)) {
			if (action == GLFW_PRESS) {
				keys.down[k] = true;
				keys.durations[k] = 0.0f;
			}
			else if (action == GLFW_RELEASE) {
				keys.down[k] = false;
			}
		}
	}

	void Input::onMouseMoveEvent(GLFWwindow *window, double x, double y) {
		mouse.position = { x, y };
	}

	void Input::onMouseButtonEvent(GLFWwindow *window, int button, int action, int mods) {
		mouse.buttons.down[button] = true;
		// TODO.
	}

	void Input::onMouseScrollEvent(GLFWwindow *window, double x, double y) {
		mouse.scrollPosition = { x, y };
	}
}