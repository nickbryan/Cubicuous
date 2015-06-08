#include "../../src/Window/Window.h"
#include "../../src/Game.h"

using Cubicuous::Debugging::Logger;
using Cubicuous::Window::Input;

int main() {
	Cubicuous::Game game(Cubicuous::Game::GameSettings(), Cubicuous::Window::WindowSettings("Cubicuous", 800, 600));

	//placeholder until loop is implemented
	while (game.getWindow()->isOpen()) {
		game.getWindow()->clear();
		game.getWindow()->update();
	}

	return 0;
}