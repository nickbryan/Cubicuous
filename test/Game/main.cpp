#include <stdlib.h>
#include "../../src/Window/Window.h"
#include "../../src/Game.h"
#include "TestScene.h"
#include "../../src/Window/WindowException.h"

using Cubicuous::Debugging::Logger;
using Cubicuous::Window::Input;

int main() {
    try {
        Cubicuous::Game game = Cubicuous::Game(new Cubicuous::GameSettings(GLFW_KEY_ESCAPE), Cubicuous::Window::WindowSettings("Cubicuous", 800, 600));

        ShaderProgram* shaderProgram = game.getShaderProgram();
        shaderProgram->attachShader("test.vert", GL_VERTEX_SHADER);
        shaderProgram->attachShader("test.frag", GL_FRAGMENT_SHADER);
        shaderProgram->bindOutput("outColor");
        shaderProgram->enable();

        game.createVertexBuffer("cubeBuffer", GL_ARRAY_BUFFER);

        game.getShaderProgram()->addVertexArray("position", 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        game.getShaderProgram()->setActiveVertexArray("position");
        game.getShaderProgram()->cacheUniform("view");
        game.getShaderProgram()->cacheUniform("projection");
        game.getShaderProgram()->cacheUniform("model");

        game.cacheScene("TestScene", new TestScene(&game));
        game.setScene("TestScene");

        // make sure we are not getting a black cube or something
        glClearColor(0.135f, 0.160f, 0.255f, 1.0f);

        game.start();
    }
    catch (Cubicuous::Graphics::GraphicsException&e) {
        Logger::log("Shader Exception", e.what());

#ifdef _WIN32
        system("PAUSE");
#endif

        return 1;
    }
    catch(Cubicuous::Window::WindowException &e) {
        Logger::log("Window Exception", e.what());

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
        #ifdef _WIN32
            Logger::log(std::current_exception().__cxa_exception_type()->name());
            system("PAUSE");
        #endif
        #ifdef __APPLE__
            Logger::log("An unknown error occurred");
        #endif

        return 1;
    }

    return 0;
}