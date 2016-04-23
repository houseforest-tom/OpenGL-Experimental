#pragma once

#include "common.h"
#include "opengl_common.h"

namespace planet {

	class Input {
	private:
		// Keyboard information.
		struct Keys {
			static const u16 KEY_LO    = GLFW_KEY_SPACE;
			static const u16 KEY_HI    = GLFW_KEY_LAST;
			static const u16 KEY_COUNT = KEY_HI - KEY_LO + 1;

			bool  down[KEY_COUNT];
			float durations[KEY_COUNT];
		};
		
		// Mouse information.
		struct Mouse {
			vec2 position;
			vec2 scrollPosition;

			struct Buttons {
				static const u16 BUTTON_COUNT = 2;

				bool  down[BUTTON_COUNT];
				float durations[BUTTON_COUNT];
			} buttons;
		};
		
		static Keys  keys;
		static Mouse mouse;

	public:
		static void install(GLFWwindow *window);
		static void update(float dt);
		static void onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void onMouseMoveEvent(GLFWwindow *window, double x, double y);
		static void onMouseButtonEvent(GLFWwindow *window, int button, int action, int mods);
		static void onMouseScrollEvent(GLFWwindow *window, double x, double y);

		static inline bool isKeyDown(u16 key) { 
			return keys.down[key - Keys::KEY_LO]; 
		}

		static inline float getKeyDownDuration(u16 key) {
			return isKeyDown(key) ? keys.durations[key - Keys::KEY_LO] : 0.0f;
		}
	};
}