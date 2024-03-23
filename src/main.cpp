#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <window.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include <iostream>
#include <shader.h>

void printv(glm::vec4 v) {
    std::cout << '[' << v.x / v.w << ", " << v.y / v.w << ", " << v.z / v.w << "]\n";
}

int main() {
    GLFWwindow* window = initialize_window(4, 1, true, true);
    clearErrors();
    // clang-format off
    float vertices[] = {
        // x, y, z, r, g, b
        1.0f, -1.0f, 2.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 2.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 8.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 8.0f, 1.0f, 0.0f, 0.0f,
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

    glm::mat4 projection;
    {
        float n = 1.0f, f = 10.0f;
        float l = -1.0f, r = 1.0f, b = -1.0f, t = 1.0f;
        glm::mat4 perspective_matrix = glm::transpose(glm::mat4x4(
            n, 0, 0, 0,
            0, n, 0, 0,
            0, 0, n + f, -f * n,
            0, 0, 1, 0));
        glm::mat4 orthographic_projection_matrix = glm::transpose(glm::mat4x4(
            2 / (r - l), 0, 0, -(r + l) / (r - l),
            0, 2 / (t - b), 0, -(t + b) / (t - b),
            0, 0, 2 / (f - n), -(f + n) / (f - n),
            0, 0, 0, 1));
        projection = orthographic_projection_matrix * perspective_matrix;
        // projection = glm::perspective(glm::degrees(tanhf(t / n)), (r - l) / (t - b), n, f);
    }

    std::cout << "\n";

    printv(projection * glm::vec4(1.0f, -1.0f, 2.0f, 1.0f));
    printv(projection * glm::vec4(1.0f, 1.0f, 8.0f, 1.0f));

    glUniformMatrix4fv(s.getUniform("u_Projection"), 1, GL_FALSE, &projection[0][0]);

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