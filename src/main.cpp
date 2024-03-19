#include <glad/glad.h>
#include <windowSetup.h>

#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    GLFWwindow* window = initialize_window(2, 1, true);

    while (!glfwWindowShouldClose(window)) {
        int width = 0, height = 0;

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(0, 1);
        glVertex2f(1, -1);
        glVertex2f(-1, -1);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}