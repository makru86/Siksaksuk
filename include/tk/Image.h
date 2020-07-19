#pragma once

#include <cstring>

#include <vector>
#include <filesystem>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace tk {

    struct Image {

        ~Image() {
            glDeleteTextures(1, &tex);
            glDeleteBuffers(1, &ebo);
            glDeleteBuffers(1, &vbo);
            glDeleteVertexArrays(1, &vao);

        }

        GLuint vao, vbo, ebo, tex;
    };

}
