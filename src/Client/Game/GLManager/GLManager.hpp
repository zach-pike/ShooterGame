#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "Utility/Logger.hpp"

class GLManager {
private:
    // This should only ever be accessed or modifed by the renderLoop function
    // as it may be running in its own thread
    GLFWwindow* window;
    Logger logger;
	
public:
    GLManager();
    ~GLManager();


    // Should be run inside a seperate thread
    void setup();
    void renderLoop();
};