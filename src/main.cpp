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
    glEnable(GL_DEPTH_TEST);
    // clang-format off
    float vertices[] = {
        // x, y, z, r, g, b
        1.0f, -1.0f, 1.0f,   0.95f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,  0.95f, 0.95f, 0.0f,
        1.0f, 1.0f, 1.0f,    0.0f, 0.95f, 0.0f,
        -1.0f, 1.0f, 1.0f,   0.0f, 0.8f, 0.95f,
        1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 0.95f,
        -1.0f, -1.0f, -1.0f,  0.0f, 0.8f, 0.95f,
        1.0f, 1.0f, -1.0f,    0.0f, 0.95f, 0.0f,
        -1.0f, 1.0f, -1.0f,   0.95f, 0.95f, 0.0f,
    };
    GLuint indices[] = {
        0, 1, 2,
        2, 1, 3,
        4, 5, 6,
        6, 5, 7,
        0, 2, 4,
        4, 2, 6,
        1, 0, 5,
        5, 0, 4,
        2, 3, 6,
        6, 3, 7,
        3, 1, 7,
        7, 1, 5,
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

    Shader s;
    s.loadShaderProgram(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");
    s.bind();

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 30.0f);
    glUniformMatrix4fv(s.getUniform("u_Projection"), 1, GL_FALSE, &projection[0][0]);

    // Place the camera at x = 10.0
    // Same as translating everything by -10.0
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(s.getUniform("u_View"), 1, GL_FALSE, &view[0][0]);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    glUniformMatrix4fv(s.getUniform("u_Model"), 1, GL_FALSE, &model[0][0]);

    getErrors();
    while (!glfwWindowShouldClose(window)) {
        clearErrors();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f)) *
                glm::rotate(glm::mat4(1.0f), 2.0f * (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f)) *
                glm::rotate(glm::mat4(1.0f), 4.0f * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f)) *
                glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f));
        glUniformMatrix4fv(s.getUniform("u_Model"), 1, GL_FALSE, &model[0][0]);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
        getErrors();
    }

    return 0;
}