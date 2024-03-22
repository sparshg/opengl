#include <glad/glad.h>
#include <window.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>

int main() {
    GLFWwindow* window = initialize_window(4, 1, true, true);
    clearErrors();

    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f};

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glBindVertexArray(0);

    Shader s;
    s.loadShaderProgram(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");
    s.bind();

    getErrors();
    while (!glfwWindowShouldClose(window)) {
        clearErrors();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
        getErrors();
    }

    return 0;
}