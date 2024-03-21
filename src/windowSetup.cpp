#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void glfwError(int id, const char* description) {
    std::cout << description << std::endl;
}

// https://learnopengl.com/In-Practice/Debugging
void GLAPIENTRY glDebugOutput(GLenum source,
                              GLenum type,
                              GLuint id,
                              GLenum severity,
                              GLsizei length,
                              const GLchar* message,
                              const void* userParam) {
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204 || id == 131222 || id == 131140 // dittering error
    )
        return;
    if (type == GL_DEBUG_TYPE_PERFORMANCE)
        return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source) {
    case GL_DEBUG_SOURCE_API:
        std::cout << "Source: API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        std::cout << "Source: Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        std::cout << "Source: Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        std::cout << "Source: Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        std::cout << "Source: Application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        std::cout << "Source: Other";
        break;
    }
    std::cout << std::endl;

    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "Type: Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "Type: Deprecated Behaviour";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "Type: Undefined Behaviour";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "Type: Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "Type: Performance";
        break;
    case GL_DEBUG_TYPE_MARKER:
        std::cout << "Type: Marker";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        std::cout << "Type: Push Group";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        std::cout << "Type: Pop Group";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "Type: Other";
        break;
    }
    std::cout << std::endl;

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "Severity: high";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "Severity: medium";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "Severity: low";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        std::cout << "Severity: notification";
        break;
    };
}

GLFWwindow* initialize_window(int versionMajor, int versionMinor, bool core = true, bool enableDebug = false) {
    glfwSetErrorCallback(&glfwError);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
    if (versionMajor >= 3 && core) {
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    GLFWwindow* window =
        glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    glfwSwapInterval(1);
    std::cout << glGetString(GL_VERSION) << std::endl;

    // report opengl errors to std
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    if (enableDebug && versionMajor >= 4 && versionMinor >= 3) {
        glDebugMessageCallback(glDebugOutput, 0);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
                              nullptr, GL_TRUE);
    }

    return window;
    // Shader s;
    // s.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH
    // "fragment.frag"); s.bind();
}
// #include <glad/glad.h>
// #define GLFW_INCLUDE_NONE
// #include <GLFW/glfw3.h>
// #include <demoShader.h>
// #include <openglDebug.h>

// #include <iostream>
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void processInput(GLFWwindow* window);

// // settings
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;

// static void glfwError(int id, const char* description) {
//     std::cout << description << std::endl;
// }

// int main(void) {
//     glfwSetErrorCallback(&glfwError);
//     if (!glfwInit()) {
//         std::cerr << "Failed to initialize GLFW" << std::endl;
//         return -1;
//     }

//     // Set OpenGL version and profile (Core in this example)
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     // Create a GLFW window
//     GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL
//     Program", NULL, NULL); if (window == NULL) {
//         std::cerr << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     // Initialize GLAD
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         std::cerr << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }
//     Shader s;
//     s.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH
//     "fragment.frag"); s.bind();

//     // Set up vertex data and buffers and configure vertex attributes
//     float vertices[] = {
//         0.5f, 0.5f, 0.0f,    // top right
//         0.5f, -0.5f, 0.0f,   // bottom right
//         -0.5f, -0.5f, 0.0f,  // bottom left
//     };
//     unsigned int VBO, VAO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     // Bind the Vertex Array Object first, then bind and set vertex
//     buffer(s), and then configure vertex attributes(s).
//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
//     GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
//     (void*)0); glEnableVertexAttribArray(0);

//     // Note that this is allowed, the call to glVertexAttribPointer
//     registered VBO as the currently bound vertex buffer object so afterwards
//     we can safely unbind glBindBuffer(GL_ARRAY_BUFFER, 0);

//     // You can unbind the VAO afterwards so other VAO calls won't
//     accidentally modify this VAO, but this rarely happens. Modifying other
//     // VAOs requires a call to glBindVertexArray anyways so we generally
//     don't unbind VAOs (nor VBOs) when it's not directly necessary.
//     glBindVertexArray(0);

//     // Render loop
//     while (!glfwWindowShouldClose(window)) {
//         processInput(window);

//         // Rendering commands here
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // Draw our first triangle
//         glBindVertexArray(VAO);
//         glDrawArrays(GL_TRIANGLES, 0, 3);

//         // Swap buffers and poll IO events
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     // Clean up
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glfwTerminate();
//     return 0;
// }

// // Function called whenever the window size is changed
// void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
// }

// // Function to process input (in this case, simply checks if the escape key
// is pressed) void processInput(GLFWwindow* window) {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, GLFW_TRUE);
// }
