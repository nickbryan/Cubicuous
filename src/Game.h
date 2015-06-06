#ifndef CUBICUOUS_GAME_H
#define CUBICUOUS_GAME_H

#include "Window/Window.h"

namespace Cubicuous {
    class Game {
        private:
            Window::Window* _window;

        public:
            inline Window::Window *getWindow() const { return this->_window; };
    };
}
#endif