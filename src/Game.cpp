#include "Game.h"

namespace Cubicuous {
    Game::Game(GameSettings *gameSettings, Cubicuous::Window::WindowSettings windowSettings) {
        this->_window = new Window::Window(windowSettings);
        this->_settings = gameSettings;
        this->_scenes = new std::unordered_map<const char *, Scene *>;

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

        if (this->_scenes != nullptr) {
            delete this->_scenes;
        }

        if (this->_settings != nullptr) {
            delete this->_settings;
        }

        if (this->_window != nullptr) {
            delete this->_window;
        }
    }

    void Game::start() {
        if (this->_running) {
            throw "Game is already running";
        }

        this->_running = true;
        while (this->_running) {
            if (this->_nextScene != nullptr) {
                if (this->_activeScene != nullptr) {
                    this->_activeScene->onInactive();
                }

                this->_previousScene = this->_activeScene;
                this->_activeScene = this->_nextScene;
                this->_activeScene->onActive();
            }

            if (this->_activeScene != nullptr) {
                this->_settings->loop->loop(this->_activeScene);
            }

            this->_window->clear();
            this->_window->update();
        }
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
}