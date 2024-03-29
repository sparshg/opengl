#include <fstream>
#include <iostream>
#include <shader.h>

// path is used for error reporting
GLint createShaderFromData(const char* data, GLenum shaderType, const char* path = 0) {
    GLuint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &data, nullptr);
    glCompileShader(shaderId);

    GLint rezult = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &rezult);

    if (!rezult) {
        char* message = 0;
        int l = 0;

        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &l);

        if (l) {
            message = new char[l];

            glGetShaderInfoLog(shaderId, l, &l, message);

            message[l - 1] = 0;

            std::cout << "error compiling shader: ";
            if (path) {
                std::cout << path;
            }
            std::cout << "\n"
                      << message << "\n";
            delete[] message;
            exit(1);
        } else {
            if (path) {
                std::cout << path << " ";
            }
            std::cout << "unknown error while compiling shader :(\n";
            exit(1);
        }

        glDeleteShader(shaderId);

        shaderId = 0;
        return shaderId;
    }

    return shaderId;
}

GLint createShaderFromFile(const char* name, GLenum shaderType) {
    std::ifstream f(name);
    std::string str;

    if (!f.is_open()) {
        std::cout << "Error opening file: " + std::string(name) << "\n";
        return 0;
    }

    f.seekg(0, std::ios::end);
    str.reserve(f.tellg());
    f.seekg(0, std::ios::beg);

    if (str.capacity() <= 0) {
        std::cout << "Error opening file: " + std::string(name) << "\n";
        return 0;
    }

    str.assign((std::istreambuf_iterator<char>(f)),
               std::istreambuf_iterator<char>());

    auto rez = createShaderFromData(str.c_str(), shaderType, name);

    return rez;
}

bool Shader::loadShaderProgram(const char* vertexShader, const char* fragmentShader) {
    auto vertexId = createShaderFromFile(vertexShader, GL_VERTEX_SHADER);
    auto fragmentId = createShaderFromFile(fragmentShader, GL_FRAGMENT_SHADER);

    if (vertexId == 0 || fragmentId == 0) {
        return 0;
    }

    id = glCreateProgram();

    glAttachShader(id, vertexId);
    glAttachShader(id, fragmentId);

    glLinkProgram(id);

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    GLint info = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &info);

    if (info != GL_TRUE) {
        char* message = 0;
        int l = 0;

        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &l);

        message = new char[l];

        glGetProgramInfoLog(id, l, &l, message);

        std::cout << std::string("Link error: ") + message << "\n";

        delete[] message;

        glDeleteProgram(id);
        id = 0;
        return 0;
    }

    glValidateProgram(id);

    return true;
}

void Shader::bind() {
    glUseProgram(id);
}

void Shader::clear() {
    glDeleteProgram(id);
    id = 0;
}

GLint Shader::getUniform(const char* name) {
    GLint uniform = glGetUniformLocation(this->id, name);
    if (uniform == -1) {
        std::cout << "uniform error " + std::string(name);
    }
    return uniform;
}