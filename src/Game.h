#ifndef CUBICUOUS_GAME_H
#define CUBICUOUS_GAME_H

#include "Window/Window.h"
#include "Core/Scene.h"
#include <unordered_map>

using Cubicuous::Core::Scene;

namespace Cubicuous {
    class Game {
    public:
	    struct GameSettings {
		    int togglePauseKey;
	    };

        private:
	    std::unordered_map<const char *, Scene *> *_scenes;
	    Scene *_activeScene = nullptr;
	    Scene *_nextScene = nullptr;
	    Window::Window *_window;
	    GameSettings _settings;

        public:
	    Game(GameSettings gameSettings, Cubicuous::Window::WindowSettings windowSettings);

	    ~Game();

	    void cacheScene(const char *name, Scene *scene);

	    inline void cacheScene(std::string name, Scene *scene) { this->cacheScene(name.c_str(), scene); }

	    inline void setScene(Scene *scene) { this->_nextScene = scene; };

	    void setScene(const char *name);

	    inline void setScene(std::string name) { this->setScene(name.c_str()); }

	    Scene *getCachedScene(const char *name) const;

	    inline Scene *getCachedScene(std::string name) const { return this->getCachedScene(name.c_str()); }

	    inline Scene *getActiveScene() const { return this->_activeScene; }

	    inline Scene *getNextScene() const { return this->_nextScene; }

	    inline Window::Window *getWindow() const { return this->_window; };
    };
}
#endif