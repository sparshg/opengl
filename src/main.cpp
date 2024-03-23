#include <glad/glad.h>
#include <window.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>

int main() {
    GLFWwindow* window = initialize_window(4, 1, true, true);
    clearErrors();
    // clang-format off
    float vertices[] = {
        // x, y, z, r, g, b
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    };
    GLuint indices[] = {
        0, 1, 2,
        2, 1, 3,
    };
    // clang-format on
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glBindVertexArray(0);

    Shader s;
    s.loadShaderProgram(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");
    s.bind();

    GLint timeLocation = s.getUniform("u_Time");
    glUniform1f(timeLocation, 0.4f);
    double offset = glfwGetTime();

    getErrors();
    while (!glfwWindowShouldClose(window)) {
        clearErrors();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform1f(timeLocation, glfwGetTime() - offset + 0.4f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
        getErrors();
    }

    return 0;
}