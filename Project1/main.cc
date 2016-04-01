#include "common.h"
#include "opengl_shader.h"
#include "opengl_buffer.h"
#include "png_loader.h"
#include "mesh.h"
#include <ctime>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

using namespace planet;

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
	GLFWwindow* window = glfwCreateWindow(800, 480, "Planet Rendering", nullptr, nullptr);
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

	// Create mesh.
	Mesh* mesh = new Mesh();

	Vertex* vertices = new Vertex[8];
	vertices[0].position = { -0.5, 0.5, 0.5 };
	vertices[1].position = { 0.5, 0.5, 0.5 };
	vertices[2].position = { 0.5, -0.5, 0.5 };
	vertices[3].position = { -0.5, -0.5, 0.5 };
	vertices[4].position = { 0.5, 0.5, -0.5 };
	vertices[5].position = { -0.5, 0.5, -0.5 };
	vertices[6].position = { -0.5, -0.5, -0.5 };
	vertices[7].position = { 0.5, -0.5, -0.5 };

	for (int i = 0; i < 8; ++i) {
		vertices[i].color = { 
			((float)rand() / RAND_MAX), 
			((float)rand() / RAND_MAX), 
			((float)rand() / RAND_MAX) 
		};
	}

	u16* indices = new u16[36] {

		0, 1, 2, // Front
		2, 3, 0,

		1, 4, 7, // Right
		7, 2, 1,

		4, 5, 6, // Back
		6, 7, 4,

		5, 0, 3, // Left
		3, 6, 5,

		5, 4, 1, // Top
		1, 0, 5,

		3, 2, 7, // Bottom
		7, 6, 3
	};

	mesh->updateVertexBuffer(
		vertices,
		8,
		GL_STATIC_DRAW
	);

	mesh->updateIndexBuffer(
		indices,
		36,
		GL_STATIC_DRAW
	);

	// Create shader program.
	OpenGLShader vs(GL_VERTEX_SHADER);
	OpenGLShader fs(GL_FRAGMENT_SHADER);
	OpenGLShaderProgram program;
	if (vs.compile("shaders/simple.vert") &&
		fs.compile("shaders/simple.frag")) {
		program.include(&vs);
		program.include(&fs);
		program.link();
	}

	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	mat4 projection = perspective(45.0f, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	mat4 view = lookAt(vec3 { 4,3,3 }, vec3 { 0,0,0 }, vec3 { 0,1,0 });
	mat4 modelViewProj = projection * view * mat4(1.0f);

	// Main loop.
	while (!glfwWindowShouldClose(window)) {
		
		// Swap buffers & handle system events.
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Clear the frame buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use the simple shader program.
		static float r = 0.0f;
		glUseProgram(program.id);
		modelViewProj = projection * view * rotate(r += 0.01f, vec3 { 0,1,0 });
		glUniformMatrix4fv(glGetUniformLocation(program.id, "modelViewProj"), 1, GL_FALSE, &modelViewProj[0][0]);	
		mesh->render();

		// Quit upon [ESC] press.
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	glfwTerminate();
	getchar();

	return 0;
}