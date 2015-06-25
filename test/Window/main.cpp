#include "../../src/Window/Window.h"

using Cubicuous::Debugging::Logger;
using Cubicuous::Window::Input;

int main() {
    Cubicuous::Window::Window window("Cubicuous", 800, 600);

    Logger::log("Renderer: " + Logger::toLoggable(glGetString(GL_RENDERER)));
    Logger::log("OpenGl Version Supported: " + Logger::toLoggable(glGetString(GL_VERSION)));
    Logger::log("GLSL version: " + Logger::toLoggable(glGetString(GL_SHADING_LANGUAGE_VERSION)));
    Logger::log("Vendor: " + Logger::toLoggable(glGetString(GL_VENDOR)));

    window.getInput()->mouseMoveListeners.push_back([&window]() {
        Logger::log(
                "Mouse pos: " + Logger::toLoggable(window.getMouseX()) + ", " + Logger::toLoggable(window.getMouseY()));
    });

    window.getInput()->mouseEnterListeners.push_back([]() {
        Logger::log("Mouse enter");
    });

    window.getInput()->mouseLeaveListeners.push_back([]() {
        Logger::log("Mouse leave");
    });

    window.getInput()->keyListeners.push_back(Input::Listener(GLFW_KEY_W, Input::State::DOWN, []() {
        Logger::log("Key w down");
    }));

    window.getInput()->keyListeners.push_back(Input::Listener(GLFW_KEY_W, Input::State::PRESS, []() {
        Logger::log("Key w press");
    }));

    window.getInput()->keyListeners.push_back(Input::Listener(GLFW_KEY_W, Input::State::UP, []() {
        Logger::log("Key w up");
    }));

    while (window.isOpen()) {
        window.clear();
        window.update();

        if (window.getInput()->isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
        }
    }

    return 0;
}