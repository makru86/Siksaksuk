#pragma once

#include <cstring>

#include <vector>
#include <filesystem>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace tk {

    struct Vec2f {
        float x;
        float y;
    };

    struct Image {
        Image(const Vec2f &topLeft, const Vec2f &bottomRight)
                : topLeft{topLeft}, bottomRight{bottomRight} {}

        ~Image() {
            glDeleteTextures(1, &tex);
            glDeleteBuffers(1, &ebo);
            glDeleteBuffers(1, &vbo);
            glDeleteVertexArrays(1, &vao);
        }

        Vec2f topLeft{}, bottomRight{};

    private:
        friend class Render;

        GLuint vao, vbo, ebo, tex;
    };

}
