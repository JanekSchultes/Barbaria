#include "Shader.h"

Shader::Shader() {

}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    std::string vertexShaderSourceString = readShaderFile(vertexShaderPath);
    std::string fragmentShaderSourceString = readShaderFile(fragmentShaderPath);
    vertexShaderSource = vertexShaderSourceString.c_str();
    fragmentShaderSource = fragmentShaderSourceString.c_str();
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    this->shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::bind() {
    glUseProgram(shaderProgram);
}

std::string Shader::readShaderFile(const char* filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream.is_open()) {
        std::cerr << "[ERROR] Could not read shader file! Aborting." << std::endl;
    }
    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

int Shader::getShaderLocation(const GLchar* variableName) {
    int returnValue = glGetUniformLocation(shaderProgram, variableName);
    return returnValue;
}

void Shader::pushMatrix4f(glm::mat4 matrix, const GLchar* name) {
    glUniformMatrix4fv(this->getShaderLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::pushFloat(float val, const GLchar* name) {
    glUniform1f(this->getShaderLocation(name), val);
}

void Shader::pushLocation2d(Vec2 loc, const GLchar* name) {
    glUniform2f(this->getShaderLocation(name), loc.x, loc.y);
}
