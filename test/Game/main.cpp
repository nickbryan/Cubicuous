#include "../../src/Window/Exception.h"
#include "../../src/Window/Window.h"
#include "../../src/Game.h"
#include "TestScene.h"
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

        game->createVertexBuffer(std::string("cubeBuffer"), GL_ARRAY_BUFFER);
        game->getShaderProgram()->addVertexArray("vertices", 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        game->createVertexBuffer("colorBuffer", GL_ARRAY_BUFFER);
        game->getShaderProgram()->addVertexArray("color", 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        game->getShaderProgram()->cacheUniform("view");
        game->getShaderProgram()->cacheUniform("projection");
        game->getShaderProgram()->cacheUniform("model");

        //now we have all our shader program data loaded, create our matrix manager
        game->getSettings()->matrixManager = new Cubicuous::Core::MatrixManager::MVPSepMatrixManager(game, "model", "projection", "view");

        //wrap in std::string because there is a bool constructor and GCC will see as const char* then casts to bool as closer than string
        game->getSettings()->geometryManager = new Cubicuous::Core::GeometryManager(game, "cubeBuffer", std::string("colorBuffer"));

        game->cacheScene("TestScene", new TestScene(game));
        game->setScene("TestScene");
        Scene *testScene = game->getCachedScene("TestScene");

        Cubicuous::Core::Structure::Structure *testStructure = new Cubicuous::Core::Structure::Structure(game);
        testStructure->addVoxel(glm::vec3(0.0f, 0.0f, 0.0f));

        testScene->addEntity(testStructure);
        testScene->addEntity(new CubeEntity(glm::vec3(-10.0f, 2.0f, 2.0f), game));
        testScene->addEntity(new CubeEntity(glm::vec3(3.0f, 3.0f, 3.0f), game));
        testScene->addEntity(new CubeEntity(glm::vec3(4.0f, 4.0f, 4.0f), game));
        testScene->addEntity(new CubeEntity(glm::vec3(5.0f, 5.0f, 5.0f), game));

        // make sure we are not getting a black cube or something
        glClearColor(0.5f, 0.7f, 1.0f, 1.0f);

        game->start();
    }
    catch(const std::exception &e) {
        Logger::log("Exception", e.what());

#ifdef _WIN32
        system("PAUSE");
#endif

        return 1;
    }
    catch(const char *e) {
        Logger::log("Exception", e);

#ifdef _WIN32
        system("PAUSE");
#endif

        return 1;
    }
    catch(...) {
        #ifdef _WIN32
            Logger::log("Exception", std::current_exception().__cxa_exception_type()->name());
            system("PAUSE");
        #endif
        #ifdef __APPLE__
            Logger::log("Exception", "An unknown error occurred");
        #endif

        return 1;
    }

    return 0;
}