#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <tk/Render.h>
#include <tk/Animation.h>

using namespace std::chrono_literals;

int main() {
    tk::Render render{};

    tk::Animation a1{};

    for (auto i{0}; i != 18; ++i) {
        std::stringstream ss{};
        ss << "../res/" << i << "_l.png";
        a1.addImage(render.loadImage(ss.str().c_str(), {-0.5f, 0.5f}, {0.0f, -0.5f}),
                    0.4s);
    }

    const auto o2{render.loadImage("../res/0_r.png", {0.0f, 0.5f}, {0.5f, -0.5f})};

    tk::Clock clock{};

    while (!glfwWindowShouldClose(render.window)) {
        glfwPollEvents();
        if (glfwGetKey(render.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(render.window, GL_TRUE);
        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render.drawImage(a1.getCurrentImage());
        render.drawImage(o2);

        a1.update(clock.getElapsedTime());

        glfwSwapBuffers(render.window);

        clock.reset();

    }

}