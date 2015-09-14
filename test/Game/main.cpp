#include "../../src/Window/Window.h"
#include "../../src/Game.h"
#include "TestScene.h"
#include "../../src/Window/WindowException.h"
#include "CubeEntity.h"
#include "../../src/Core/MatrixManager/MVPSepMatrixManager.h"
#include "../../src/Core/Structure/Structure.h"
#include "../../src/Core/Structure/Voxel.h"

using Cubicuous::Debugging::Logger;
using Cubicuous::Window::Input;

int main() {
    try {
        Cubicuous::Game* game = new Cubicuous::Game(new Cubicuous::GameSettings(60, GLFW_KEY_ESCAPE), Cubicuous::Window::WindowSettings("Cubicuous", 800, 600));

        // Set the curser to 0,0 so we can work out delta movements
        game->getWindow()->resetMousePosition();
        game->getWindow()->lockCursor();

        ShaderProgram* shaderProgram = game->getShaderProgram();
        shaderProgram->attachShader("test.vert", GL_VERTEX_SHADER);
        shaderProgram->attachShader("test.frag", GL_FRAGMENT_SHADER);
        shaderProgram->bindOutput("outColor");
        shaderProgram->enable();

        game->createVertexBuffer("cubeBuffer", GL_ARRAY_BUFFER);
        game->getShaderProgram()->addVertexArray("vertices", 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        game->createVertexBuffer("colorBuffer", GL_ARRAY_BUFFER);
        game->getShaderProgram()->addVertexArray("color", 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        game->getShaderProgram()->cacheUniform("view");
        game->getShaderProgram()->cacheUniform("projection");
        game->getShaderProgram()->cacheUniform("model");

        //now we have all our shader program data loaded, create our matrix manager
        game->getSettings()->matrixManager = new Cubicuous::Core::MatrixManager::MVPSepMatrixManager(game, "model", "projection", "view");
        game->getSettings()->geometryManager = new Cubicuous::Core::GeometryManager(game, "cubeBuffer", "colorBuffer");

        game->cacheScene("TestScene", new TestScene(game));
        game->setScene("TestScene");
        Scene *testScene = game->getCachedScene("TestScene");

        Cubicuous::Core::Structure::Structure *testStructure = new Cubicuous::Core::Structure::Structure(game);

        //testScene->addEntity(new CubeEntity(glm::vec3(1.0f, 1.0f, 1.0f), &game));
        testScene->addEntity(testStructure);
        testScene->addEntity(new CubeEntity(glm::vec3(-10.0f, 2.0f, 2.0f), game));
        testScene->addEntity(new CubeEntity(glm::vec3(3.0f, 3.0f, 3.0f), game));
        testScene->addEntity(new CubeEntity(glm::vec3(4.0f, 4.0f, 4.0f), game));
        testScene->addEntity(new CubeEntity(glm::vec3(5.0f, 5.0f, 5.0f), game));

        // make sure we are not getting a black cube or something
        glClearColor(0.5f, 0.7f, 1.0f, 1.0f);

        game->start();
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