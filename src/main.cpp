#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common/shader.hpp"

static GLFWwindow* window;
static GLuint vertex_arr_id, vertex_buffer, color_buffer, shader_id;

static const GLfloat vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
};

int main() {
    glfwSetErrorCallback([] (int error_core, const char *description) -> void {
        fprintf(stderr, description);
    });

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        system("pause");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(1024, 768, "OpenGL Setup", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();

        std::cerr << "Failed to open GLFW window" << std::endl;
        system("pause");
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();

        std::cerr << "Failed to initialize GLEW" << std::endl;
        system("pause");
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSwapInterval(1);

    // load shaders
    shader_id = loadShader("color.vert", "color.frag");

    // vertex array object
    glGenVertexArrays(1, &vertex_arr_id);
    glBindVertexArray(vertex_arr_id);

    // buffers
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // setup shaders
        glUseProgram(shader_id);

        // draw triangle
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &color_buffer);
    glDeleteProgram(shader_id);
    glDeleteVertexArrays(1, &vertex_arr_id);

    glfwTerminate();

    return 0;
}
