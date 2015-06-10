#include "../../src/Window/Window.h"
#include "../../src/Game.h"

using Cubicuous::Debugging::Logger;
using Cubicuous::Window::Input;

int main() {
    Cubicuous::Game game(new Cubicuous::Game::GameSettings(GLFW_KEY_ESCAPE),
                         Cubicuous::Window::WindowSettings("Cubicuous", 800, 600));
    game.start();

    return 0;
}