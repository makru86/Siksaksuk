#include <iostream>

#include "Player.h"

using namespace std::chrono_literals;

int main() {
    tk::Render render{};

    Player p1{render};

    const auto o2{render.loadImage("../res/0_r.png", {0.0f, 0.5f}, {0.5f, -0.5f})};

    tk::Clock clock{};

    while (!glfwWindowShouldClose(render.window)) {
        glfwPollEvents();
        if (glfwGetKey(render.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(render.window, GL_TRUE);
        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(render.window, GLFW_KEY_A) == GLFW_PRESS) {
            p1.setState(Player::State::Paper);
        }
        auto &a1{p1.getAnimation()};

        render.drawImage(a1.getCurrentImage());
        render.drawImage(o2);

        a1.update(clock.getElapsedTime());

        glfwSwapBuffers(render.window);

        clock.reset();
    }

}