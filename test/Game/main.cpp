#include "../../src/Window/Window.h"
#include "../../src/Game.h"
#include "TestScene.h"

using Cubicuous::Debugging::Logger;
using Cubicuous::Window::Input;

int main() {
    Cubicuous::Game game(new Cubicuous::Game::GameSettings(GLFW_KEY_ESCAPE),
                         Cubicuous::Window::WindowSettings("Cubicuous", 800, 600));

    game.cacheScene("TestScene", new TestScene());
    game.setScene("TestScene");

    game.start();

    return 0;
}