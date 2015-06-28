#include "Game.h"

namespace Cubicuous {
    Game::Game(GameSettings *gameSettings, Cubicuous::Window::WindowSettings windowSettings) {
        this->_window = new Window::Window(windowSettings);
        glfwSetWindowUserPointer(this->getWindow()->getWindow(), this);
        glfwSetKeyCallback(this->getWindow()->getWindow(), Input::keyCallback);
        glfwSetMouseButtonCallback(this->getWindow()->getWindow(), Input::mouseButtonCallback);

        this->_settings = gameSettings;
        this->_scenes = new std::unordered_map<const char *, Scene *>;

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

        if (this->_scenes != nullptr) {
            delete this->_scenes;
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
            throw "Game is already running";
        }

        this->_running = true;

        while (this->_running) {
            this->_window->clear();

            if (this->_nextScene != nullptr) {
                if (this->_activeScene != nullptr) {
                    this->_activeScene->onInactive();
                }

                this->_previousScene = this->_activeScene;
                this->_activeScene = this->_nextScene;
                this->_activeScene->onActive();

                if(this->_previousScene == this->_settings->pauseScene) {
                    this->_activeScene->onPlay();
                }

                this->_nextScene = nullptr;
            }

            if (this->_activeScene != nullptr) {
                this->_shaderProgram->enable();
                this->_shaderProgram->reloadActiveVertexArray();
                this->_settings->loop->loop(this);
            }

            this->_window->postRender();
        }

        //stop code
        this->_shaderProgram->disable();
    }

    void Game::cacheScene(const char *name, Scene *scene) {
        if (this->_scenes->find(name) != this->_scenes->end()) {
            throw "Scene already cached";
        }

        this->_scenes->insert(std::pair<const char *, Scene *>(name, scene));
    }

    void Game::setScene(const char *name) {
        Scene *setTo = this->getCachedScene(name);

        if (setTo == nullptr) {
            throw "Scene not found";
        }

        this->setScene(setTo);
    }

    Scene *Game::getCachedScene(const char *name) const {
        std::unordered_map<const char *, Scene *>::const_iterator iterator = this->_scenes->find(name);

        if (iterator == this->_scenes->end()) {
            return nullptr;
        }

        return iterator->second;
    }

    VertexBuffer* Game::createVertexBuffer(const char* name, GLenum type) {
        VertexBuffer* vertexBuffer = new VertexBuffer(type);
        this->_vertexBuffers.insert(std::pair<const char*, VertexBuffer*>(name, vertexBuffer));
        return vertexBuffer;
    }

    void Game::createVertexBuffer(const char* name, GLuint id, GLenum storageMode, GLenum type) {
        this->_vertexBuffers.insert(std::pair<const char*, VertexBuffer*>(name, new VertexBuffer(type, storageMode, id)));
    }

    void Game::attachVertexBuffer(const char* name, VertexBuffer* buffer) {
        this->_vertexBuffers.insert(std::pair<const char*, VertexBuffer*>(name, buffer));
    }

    VertexBuffer* Game::getVertexBuffer(const char* name) {
        std::unordered_map<const char*, VertexBuffer*>::iterator iterator = this->_vertexBuffers.find(name);

        if (iterator == this->_vertexBuffers.end()) {
            throw "Buffer not found.";
        }

        return (*iterator).second;
    }
}