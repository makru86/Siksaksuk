#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <tk/Render.h>

int main() {
    tk::Render render{};

    const auto o1{render.loadImage("../res/0_l.png", {-0.5f, 0.5f}, {0.0f, -0.5f})};

    const auto o2{render.loadImage("../res/0_r.png", {0.0f, 0.5f}, {0.5f, -0.5f})};

    while (!glfwWindowShouldClose(render.window)) {
        glfwPollEvents();
        if (glfwGetKey(render.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(render.window, GL_TRUE);
        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render.drawImage(o1);
        render.drawImage(o2);

        glfwSwapBuffers(render.window);
    }

}