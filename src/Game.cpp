#include "Game.h"
#include "Core/Scene.h"

namespace Cubicuous {
    Game::Game(GameSettings *gameSettings, Cubicuous::Window::WindowSettings windowSettings) {
        this->_window = new Window::Window(windowSettings);
        glfwSetWindowUserPointer(this->getWindow()->getWindow(), this);
        glfwSetKeyCallback(this->getWindow()->getWindow(), Input::keyCallback);
        glfwSetMouseButtonCallback(this->getWindow()->getWindow(), Input::mouseButtonCallback);

        this->_settings = gameSettings;

        glGenVertexArrays(1, &this->_vertexArrayID);
        glBindVertexArray(this->_vertexArrayID);
        this->_shaderProgram = new ShaderProgram();

        if (this->_settings->quickQuitKey != 0) {
            this->_window->getInput()->keyListeners.push_back(
                    Cubicuous::Window::Input::Listener(this->_settings->quickQuitKey,
                                                       Cubicuous::Window::Input::State::PRESS, [this]() {
                                this->stop();
                                this->_window->close();
                            }));
        }

        if (this->_settings->togglePauseKey != 0) {
            this->_window->getInput()->keyListeners.push_back(
                    Cubicuous::Window::Input::Listener(this->_settings->togglePauseKey,
                                                       Cubicuous::Window::Input::State::PRESS, [this]() {
                                if(this->_activeScene != nullptr) {
                                    this->_activeScene->onPause();
                                }

                                this->setScene(this->_settings->pauseScene);
                            }));
        }
    }

    Game::~Game() {
        if (this->_activeScene != nullptr && this->_activeScene != this->_settings->pauseScene) {
            delete this->_activeScene;
        }
        if (this->_nextScene != nullptr && this->_nextScene != this->_settings->pauseScene) {
            delete this->_nextScene;
        }
        if(this->_previousScene != nullptr && this->_previousScene != this->_settings->pauseScene) {
            delete this->_previousScene;
        }

        glDeleteVertexArrays(1, &this->_vertexArrayID);
        if (this->_settings != nullptr) {
            delete this->_settings;
        }

        if (this->_window != nullptr) {
            delete this->_window;
        }

        if (this->_shaderProgram != nullptr) {
            delete this->_shaderProgram;
        }
    }

    void Game::start() {
        if (this->_running) {
            throw Core::Exception("Game is already running");
        }

        this->_running = true;
        this->getShaderProgram()->enable();

        while (this->isRunning()) {
            this->getWindow()->clear();

            if (this->getNextScene() != nullptr) {
                if (this->getActiveScene() != nullptr) {
                    this->getActiveScene()->onInactive();
                }

                this->_previousScene = this->getActiveScene();
                this->_activeScene = this->getNextScene();
                this->getActiveScene()->onActive();

                if(this->getPreviousScene() == this->getSettings()->pauseScene) {
                    this->getActiveScene()->onPlay();
                }

                this->_nextScene = nullptr;
            }

            if (this->getActiveScene() != nullptr) {
                this->getShaderProgram()->reloadActiveVertexArray();
                this->getSettings()->loop->loop(this);
            }

            this->getWindow()->postRender();
        }

        //stop code
        this->getShaderProgram()->disable();
    }

    void Game::cacheScene(std::string name, Scene *scene) {
        if (this->_scenes.find(name) != this->_scenes.end()) {
            throw Core::Exception("Scene already cached");
        }

        this->_scenes.insert(std::pair<std::string, Scene *>(name, scene));
    }

    void Game::setScene(std::string name) {
        Scene *setTo = this->getCachedScene(name);

        if (setTo == nullptr) {
            throw Core::Exception("Scene not found");
        }

        this->setScene(setTo);
    }

    Scene *Game::getCachedScene(std::string name) const {
        std::unordered_map<std::string, Scene *>::const_iterator iterator = this->_scenes.find(name);

        if (iterator == this->_scenes.end()) {
            Debugging::Logger::log("Failed to find cached scene " + Debugging::Logger::toLoggable(name));
            return nullptr;
        }

        return iterator->second;
    }

    VertexBuffer* Game::createVertexBuffer(std::string name, GLenum type) {
        VertexBuffer* vertexBuffer = new VertexBuffer(type);
        this->_vertexBuffers.insert(std::pair<std::string, VertexBuffer*>(name, vertexBuffer));
        return vertexBuffer;
    }

    void Game::createVertexBuffer(std::string name, GLuint id, GLenum storageMode, GLenum type) {
        this->_vertexBuffers.insert(std::pair<std::string, VertexBuffer*>(name, new VertexBuffer(type, storageMode, id)));
    }

    void Game::attachVertexBuffer(std::string name, VertexBuffer* buffer) {
        this->_vertexBuffers.insert(std::pair<std::string, VertexBuffer*>(name, buffer));
    }

    VertexBuffer* Game::getVertexBuffer(std::string name) const {
        std::unordered_map<std::string, VertexBuffer*>::const_iterator iterator = this->_vertexBuffers.find(name);

        if (iterator == this->_vertexBuffers.end()) {
            Debugging::Logger::log("Failed to find buffer " + Debugging::Logger::toLoggable(name));
            return nullptr;
        }

        return (*iterator).second;
    }
}