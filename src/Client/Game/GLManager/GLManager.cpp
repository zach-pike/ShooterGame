#include "GLManager.hpp"

#include <vector>

#include "Client/GL/Shader/Shader.hpp"
#include "Client/GL/Buffer/Buffer.hpp"

GLManager::GLManager():
    logger("GLManager", Logger::FGColors::GREEN) {}
GLManager::~GLManager() {}

void GLManager::setup() {
    // Initialize GLFW
	if(!glfwInit()) {
		logger.error("Error initializing glfw!");

        exit(0);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make macOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "ShooterGame", NULL, NULL);
	if (window == nullptr) {
		logger.error("Error creating glfw window!");
		
        exit(0);
	}

    glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		logger.error("Error initializing GLEW!");
		
        exit(0);
	}

    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void GLManager::renderLoop() {
    // Create the VAO
	GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

    Shader shaderProgram("resources/shader/vertex.glsl", "resources/shader/fragment.glsl");
    shaderProgram.loadShaders();
    shaderProgram.useShader();


    Buffer<GLfloat> buffer;
    std::vector<GLfloat> data = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};
    buffer.bufferData(data);

    do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, buffer.getBufferID());
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, data.size() / 3);

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    shaderProgram.unloadShader();
    buffer.uninit();

    glDeleteVertexArrays(1, &vertexArrayID);

    glfwTerminate();
}