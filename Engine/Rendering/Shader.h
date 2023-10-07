#ifndef SHADER
#define SHADER

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Utils/math_utils.h"

class Shader {
public:
    Shader();
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    void bind();
    std::string readShaderFile(const char* filePath);
    int getShaderLocation(const GLchar* variableName);
    void pushMatrix4f(glm::mat4 matrix, const GLchar* name);
    void pushFloat(float val, const GLchar* name);
    void pushLocation2d(Vec2 loc, const GLchar* name);
protected:
private:
    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    int shaderProgram = 0;
};

#endif
