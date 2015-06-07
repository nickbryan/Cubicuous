#include "../../src/Window/Window.h"

using Cubicuous::Debugging::Logger;

int main() {
	Cubicuous::Window::Window window("Cubicuous", 800, 600);

	Logger::log("Renderer: " + Logger::toLoggable(glGetString(GL_RENDERER)));
	Logger::log("OpenGl Version Supported: " + Logger::toLoggable(glGetString(GL_VERSION)));
	Logger::log("GLSL version: " + Logger::toLoggable(glGetString(GL_SHADING_LANGUAGE_VERSION)));
	Logger::log("Vendor: " + Logger::toLoggable(glGetString(GL_VENDOR)));

	while (window.isOpen()) {
		window.clear();
		window.update();

        if (window.getInput()->isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
        }
	}

	return 0;
}