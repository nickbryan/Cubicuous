#include <stdlib.h>
#include "../../src/Window/Window.h"
#include "../../src/Game.h"
#include "TestScene.h"

using Cubicuous::Debugging::Logger;
using Cubicuous::Window::Input;

int main() {
    try {
        Cubicuous::Game game = Cubicuous::Game(new Cubicuous::GameSettings(GLFW_KEY_ESCAPE), Cubicuous::Window::WindowSettings("Cubicuous", 800, 600));

        ShaderProgram* shaderProgram = game.getShaderProgram();
        shaderProgram->attachShader("test.vert", GL_VERTEX_SHADER);
        shaderProgram->attachShader("test.frag", GL_FRAGMENT_SHADER);
        shaderProgram->bindOutput("outColor");

        game.createVertexBuffer("cubeBuffer", GL_ARRAY_BUFFER);
        game.createVertexBuffer("colorBuffer", GL_ARRAY_BUFFER);

        game.cacheScene("TestScene", new TestScene(&game));
        game.setScene("TestScene");

        game.start();
    }
    catch (Cubicuous::Graphics::ShaderException &e) {
        Logger::log("Shader Exception", e.what());

#ifdef _WIN32
        system("PAUSE");
#endif

        return 1;
    }
    catch(const std::exception &e) {
        Logger::log(e.what());

#ifdef _WIN32
        system("PAUSE");
#endif

        return 1;
    }
    catch(const char *e) {
        Logger::log(e);

#ifdef _WIN32
        system("PAUSE");
#endif

        return 1;
    }
    catch(...) {
        Logger::log(std::current_exception().__cxa_exception_type()->name());

#ifdef _WIN32
        system("PAUSE");
#endif

        return 1;
    }

    return 0;
}