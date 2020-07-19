#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <tk/Render.h>

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    const auto *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "OpenGL", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    tk::Render render{};

    const auto o1{render.loadImage("../res/0_l.png", {
            -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f})};

    const auto o2{render.loadImage("../res/0_r.png", {
            0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f})};

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render.drawImage(o1);
        render.drawImage(o2);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}