#include <glad/glad.h>
#include <windowSetup.h>

#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    GLFWwindow* window = initialize_window(2, 1, true);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        // glColor3f(1, 0, 0);
        glVertex2f(0, 1);
        // glColor3f(0, 1, 0);
        glVertex2f(1, -1);
        // glColor3f(0, 0, 1);
        glVertex2f(-1, -1);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}