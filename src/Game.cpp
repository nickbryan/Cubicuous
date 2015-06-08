#include "Game.h"

namespace Cubicuous {
    Game::Game(GameSettings gameSettings, Cubicuous::Window::WindowSettings windowSettings) {
	    this->_window = new Window::Window(windowSettings);
	    this->_settings = gameSettings;
	    this->_scenes = new std::unordered_map<const char *, Scene *>;
    }

    Game::~Game() {
	    if (this->_activeScene != nullptr) {
		    delete(&this->_activeScene);
	    }
	    if (this->_nextScene != nullptr) {
		    delete(&this->_nextScene);
	    }

	    delete(&this->_scenes);
	    delete(&this->_settings);
	    delete(&this->_window);
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