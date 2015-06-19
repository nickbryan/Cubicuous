#include <stdlib.h>
#include "../../src/Window/Window.h"
#include "../../src/Game.h"
#include "TestScene.h"

using Cubicuous::Debugging::Logger;
using Cubicuous::Window::Input;

int main() {
    try {
        Cubicuous::Game game = Cubicuous::Game(new Cubicuous::GameSettings(GLFW_KEY_ESCAPE), Cubicuous::Window::WindowSettings("Cubicuous", 800, 600));
        game.cacheScene("TestScene", new TestScene(&game));
        game.setScene("TestScene");

        float cubeSize = 0.5f;

        GLfloat cube1[] = {
                // back
                -cubeSize, -cubeSize, -cubeSize, cubeSize, -cubeSize, -cubeSize, cubeSize, cubeSize, -cubeSize, cubeSize,
                cubeSize, -cubeSize, -cubeSize, cubeSize, -cubeSize, -cubeSize, -cubeSize, -cubeSize,

                // front
                -cubeSize, -cubeSize, cubeSize, cubeSize, -cubeSize, cubeSize, cubeSize, cubeSize, cubeSize, cubeSize,
                cubeSize, cubeSize, -cubeSize, cubeSize, cubeSize, -cubeSize, -cubeSize, cubeSize,

                // left
                -cubeSize, cubeSize, cubeSize, -cubeSize, cubeSize, -cubeSize, -cubeSize, -cubeSize, -cubeSize, -cubeSize, -cubeSize, -cubeSize,
                -cubeSize, -cubeSize, cubeSize, -cubeSize, cubeSize, cubeSize,

                // right
                cubeSize, cubeSize, cubeSize, cubeSize, cubeSize, -cubeSize, cubeSize, -cubeSize, -cubeSize, cubeSize, -cubeSize, -cubeSize,
                cubeSize, -cubeSize, cubeSize, cubeSize, cubeSize, cubeSize,

                // bottom
                -cubeSize, -cubeSize, -cubeSize, cubeSize, -cubeSize, -cubeSize, cubeSize, -cubeSize, cubeSize, cubeSize, -cubeSize,
                cubeSize, -cubeSize, -cubeSize, cubeSize, -cubeSize, -cubeSize, -cubeSize,

                // top
                -cubeSize, cubeSize, -cubeSize, cubeSize, cubeSize, -cubeSize, cubeSize, cubeSize, cubeSize, cubeSize,
                cubeSize, cubeSize, -cubeSize, cubeSize, cubeSize, -cubeSize, cubeSize, -cubeSize};

        GLfloat color[] = {0.583f, 0.771f, 0.014f, 0.583f, 0.771f, 0.014f, 0.583f, 0.771f, 0.014f,

                           0.583f, 0.771f, 0.014f, 0.583f, 0.771f, 0.014f, 0.583f, 0.771f, 0.014f,

                           0.597f, 0.770f, 0.761f, 0.597f, 0.770f, 0.761f, 0.597f, 0.770f, 0.761f,

                           0.597f, 0.770f, 0.761f, 0.597f, 0.770f, 0.761f, 0.597f, 0.770f, 0.761f,

                           0.014f, 0.184f, 0.576f, 0.014f, 0.184f, 0.576f, 0.014f, 0.184f, 0.576f,

                           0.014f, 0.184f, 0.576f, 0.014f, 0.184f, 0.576f, 0.014f, 0.184f, 0.576f,

                           0.997f, 0.513f, 0.064f, 0.997f, 0.513f, 0.064f, 0.997f, 0.513f, 0.064f,

                           0.997f, 0.513f, 0.064f, 0.997f, 0.513f, 0.064f, 0.997f, 0.513f, 0.064f,

                           0.055f, 0.953f, 0.042f, 0.055f, 0.953f, 0.042f, 0.055f, 0.953f, 0.042f,

                           0.055f, 0.953f, 0.042f, 0.055f, 0.953f, 0.042f, 0.055f, 0.953f, 0.042f,

                           0.517f, 0.713f, 0.338f, 0.517f, 0.713f, 0.338f, 0.517f, 0.713f, 0.338f,

                           0.517f, 0.713f, 0.338f, 0.517f, 0.713f, 0.338f, 0.517f, 0.713f, 0.338f,};


        VertexBuffer cube = game.createVertexBuffer("cubeBuffer", GL_ARRAY_BUFFER);
        cube.updateData(&cube1);

        ShaderProgram* shaderProgram = game.getShaderProgram();
        shaderProgram->attachShader("test.vert", GL_VERTEX_SHADER);
        shaderProgram->attachShader("test.frag", GL_FRAGMENT_SHADER);
        shaderProgram->bindFragDataLocation("outcolor");
        shaderProgram->enable();
        shaderProgram->setVertexAttribArray("position", 3, GL_FLOAT, GL_FALSE, 0, 0);

        game.createVertexBuffer("colorBuffer", GL_ARRAY_BUFFER);
        VertexBuffer colorBuffer = game.getVertexBuffer("colorBuffer");
        colorBuffer.updateData(&color);
        shaderProgram->setVertexAttribArray("color", 3, GL_FLOAT, GL_FALSE, 0, 0);

        game.start();
    }
    catch (Cubicuous::Graphics::ShaderException &e) {
        Logger::log("Shader Exception", e.what());

#ifdef _WIN32
        system("PAUSE");
#endif

        return 1;
    }

    return 0;
}