#pragma once
#include "GLFW/glfw3.h"

void GLAPIENTRY glDebugOutput(GLenum source,
                              GLenum type,
                              GLuint id,
                              GLenum severity,
                              GLsizei length,
                              const GLchar* message,
                              const void* userParam);
void clearErrors();
void getErrors();
GLFWwindow* initialize_window(int versionMajor, int versionMinor, bool core, bool enableDebug);