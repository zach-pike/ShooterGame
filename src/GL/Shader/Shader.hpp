#pragma once

#include <GL/glew.h>

#include "Utility/Logger.hpp"

#include <string>

class Shader {
private:
    bool shaderLoaded = false;
    GLuint program;

    std::string vertexFilePath;
    std::string fragmentFilePath;

    Logger logger;

public:
    Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    ~Shader();

    void loadShaders();
    void unloadShader();

    bool isShaderLoaded() const;

    void useShader();
};