#pragma once

#include <cstring>

#include <vector>
#include <filesystem>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <tk/Image.h>

namespace tk {

    struct Render {
        Render() {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

            const auto *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

            window = glfwCreateWindow(mode->width, mode->height, "OpenGL", nullptr, nullptr);

            glfwMakeContextCurrent(window);

            glewExperimental = GL_TRUE;
            glewInit();

            // Create and compile the vertex shader
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexSource, NULL);
            glCompileShader(vertexShader);

            // Create and compile the fragment shader
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
            glCompileShader(fragmentShader);

            // Link the vertex and fragment shader into a shader program
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glBindFragDataLocation(shaderProgram, 0, "outColor");
            glLinkProgram(shaderProgram);

        }

        Image loadImage(const char *png, const Vec2f &topLeft, const Vec2f &bottomRight) {
            Image image{topLeft, bottomRight};

            std::vector<GLfloat> vertices{
                    image.topLeft.x, image.topLeft.y, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    image.bottomRight.x, image.topLeft.y, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                    image.bottomRight.x, image.bottomRight.y, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                    image.topLeft.x, image.bottomRight.y, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f};

            // Create Vertex Array Object
            glGenVertexArrays(1, &image.vao);
            glBindVertexArray(image.vao);

            // Create a Vertex Buffer Object and copy the vertex data to it
            glGenBuffers(1, &image.vbo);

            glBindBuffer(GL_ARRAY_BUFFER, image.vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

            // Create an element array
            glGenBuffers(1, &image.ebo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, image.ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);

            // Specify the layout of the vertex data
            GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
            glEnableVertexAttribArray(posAttrib);
            glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

            GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
            glEnableVertexAttribArray(colAttrib);
            glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),
                                  (void *) (2 * sizeof(GLfloat)));

            GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
            glEnableVertexAttribArray(texAttrib);
            glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),
                                  (void *) (5 * sizeof(GLfloat)));

            // Load texture
            glGenTextures(1, &image.tex);
            glBindTexture(GL_TEXTURE_2D, image.tex);

            int width, height;
            unsigned char *data = SOIL_load_image(png, &width, &height, 0, SOIL_LOAD_RGB);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            SOIL_free_image_data(data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            return image;
        }


        void drawImage(const Image &image) {
            glUseProgram(shaderProgram);
            glBindVertexArray(image.vao);
            glBindBuffer(GL_ARRAY_BUFFER, image.vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, image.ebo);
            glBindTexture(GL_TEXTURE_2D, image.tex);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        ~Render() {
            glDeleteProgram(shaderProgram);
            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            glfwTerminate();
        }

        GLFWwindow *window;
        GLuint shaderProgram, fragmentShader, vertexShader;
        std::vector<GLuint> elements = {0, 1, 2,
                                        2, 3, 0};
        const GLchar *vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    in vec3 color;
    in vec2 texcoord;
    out vec3 Color;
    out vec2 Texcoord;
    void main()
    {
        Color = color;
        Texcoord = texcoord;
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";
        const GLchar *fragmentSource = R"glsl(
    #version 150 core
    in vec3 Color;
    in vec2 Texcoord;
    out vec4 outColor;
    uniform sampler2D tex;
    void main()
    {
        outColor = texture(tex, Texcoord) * vec4(Color, 1.0);
    }
)glsl";

    };

}
