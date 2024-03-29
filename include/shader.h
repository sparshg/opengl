#pragma once
#include <glad/glad.h>

struct Shader {
    GLuint id = 0;

    bool loadShaderProgram(const char* vertexShader, const char* fragmentShader);

    void bind();

    void clear();

    GLint getUniform(const char* name);
};