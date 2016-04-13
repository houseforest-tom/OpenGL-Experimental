#include <ctime>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

#include "common.h"
#include "opengl_shader.h"
#include "opengl_buffer.h"
#include "png_loader.h"
#include "mesh.h"
#include "scene.h"
#include "cube_entity.h"

using namespace planet;

class MainScene : public Scene {
private:
	GLFWwindow* window;
	mat4 projectionMatrix;
	mat4 viewMatrix;

	OpenGLShader* vertexShader;
	OpenGLShader* fragmentShader;
	OpenGLShaderProgram* shaderProgram;

public:
	MainScene(GLFWwindow* window) {
		this->window = window;
		addEntity("cube", new CubeEntity());

		// Create shader program.
		vertexShader = new OpenGLShader(GL_VERTEX_SHADER);
		fragmentShader = new OpenGLShader(GL_FRAGMENT_SHADER);
		shaderProgram = new OpenGLShaderProgram();
		if (vertexShader->compile("shaders/simple.vert") &&
			fragmentShader->compile("shaders/simple.frag")) {
			shaderProgram->include(vertexShader);
			shaderProgram->include(fragmentShader);
			shaderProgram->link();
		}

		int windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		projectionMatrix = perspective(45.0f, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
		viewMatrix = lookAt(vec3 { 4,3,3 }, vec3 { 0,0,0 }, vec3 { 0,1,0 });
	}

	void update(float dt) {
		Scene::update(dt);
		glUniformMatrix4fv(
			glGetUniformLocation(shaderProgram->id, "modelViewProj"),
			1,
			GL_FALSE,
			&((ModelComponent*)(getEntity("cube")->getComponent("model")))->modelMatrix[0][0]
		);
	}

	void render() {
		// Use the simple shader program.
		glUseProgram(shaderProgram->id);
		Scene::render();
	}

	~MainScene() {
		delete shaderProgram;
		delete fragmentShader;
		delete vertexShader;
	}
};

int main() {
	srand(time(nullptr));

	// Initialize GLFW library.
	if (!glfwInit()) {
		logMessage("GLFW initialization failed.", Loglevel::error);
		exit(-1);
	}
	else {
		logMessage("Successfully initialized GLFW.");
	}

	// Set OpenGL context settings.
	u32 gl_version = 45;  // Use OpenGL 4.5
	u32 msaa_samples = 4; // Use 4x MSAA.
	glfwWindowHint(GLFW_SAMPLES, msaa_samples);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version / 10);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version % 10);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window.
	GLFWwindow* window = glfwCreateWindow(1440, 900, "Planet Rendering", nullptr, nullptr);
	if (window == nullptr) {
		logMessage("Window creation failed.", Loglevel::error);
		glfwTerminate();
		exit(-1);
	}
	else {
		logMessage("Successfully created window.");
		glfwMakeContextCurrent(window);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);
	}

	// Initialize GLEW library.
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		logMessage("GLEW initialization failed.", Loglevel::error);
		glfwTerminate();
		exit(-1);
	}
	else {
		logMessage("Successfully initialized GLEW.");
		logMessage("Using OpenGL version: " + string((const char *)glGetString(GL_VERSION)));

		// Enable depth testing.
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	Scene* scene = new MainScene(window);

	// Main loop.
	while (!glfwWindowShouldClose(window)) {
		
		// Swap buffers & handle system events.
		glfwSwapBuffers(window);
		glfwPollEvents();

		scene->update(1 / 60.f);

		// Clear the frame buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene->render();

		// Quit upon [ESC] press.
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	delete scene;
	glfwTerminate();
	return 0;
}