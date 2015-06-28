#include "Input.h"
#include "../Game.h"

namespace Cubicuous {
    namespace Window {
        Input::Input(Window *windowPointer, bool useFocus, float x, float y, int width, int height) {
            this->_window = windowPointer;
            this->_boundX = x;
            this->_boundY = y;
            this->_boundWidth = width;
            this->_boundHeight = height;
            this->_useFocus = useFocus;

            for (int i = 0; i < MAX_KEYS; i++) {
                this->_keys[i] = false;
            }

            for (int i = 0; i < MAX_MOUSE_BUTTONS; i++) {
                this->_mouseButtons[i] = false;
            }
        }

        Input::Input(Window *windowPointer, float x, float y, int width, int height) : Input(windowPointer, false, x, y,
                                                                                             width, height) { }

        Input::Input(Window *windowPointer, bool useFocus) : Input(windowPointer, useFocus, 0, 0,
                                                                   windowPointer->getWidth(),
                                                                   windowPointer->getHeight()) { }

        Input::Input(Window *windowPointer) : Input(windowPointer, false) { }

        Input::~Input() {
        }

        void Input::processEvents() {
            if (!this->_window->isFocused()) {
                return;
            }

            /* Key events */
            for (Listener &listener : this->keyListeners) {
                if (this->_keys[listener.key] && listener.state == State::DOWN) {
                    listener.handler();
                }
            }

            /* Mouse events */
            if (this->isMouseOver()) {
                if (!this->wasMouseOver()) {
                    for (auto &listener : this->mouseEnterListeners) {
                        listener();
                    }
                }

                if (this->_window->getPreviousMouseX() != this->_window->getMouseX() ||
                    this->_window->getPreviousMouseY() != this->_window->getMouseY()) {
                    for (auto &listener : this->mouseMoveListeners) {
                        listener();
                    }
                }

                for (Listener &listener : this->mouseListeners) {
                    if (this->_mouseButtons[listener.key] && listener.state == State::DOWN) {
                        listener.handler();
                    }
                }
            }
            else if (this->wasMouseOver()) {
                for (auto &listener : this->mouseLeaveListeners) {
                    listener();
                }
            }
        }

        bool Input::isKeyPressed(unsigned int keyCode) const {
            return (!this->_useFocus || this->focused) && this->_keys[keyCode];
        }

        bool Input::isMouseButtonPressed(unsigned int buttonCode) const {
            return this->isMouseOver() && this->_mouseButtons[buttonCode];
        }

        bool Input::isMouseOver() const {
            return this->_window->isFocused() && this->_window->getMouseX() >= this->_boundX &&
                   this->_window->getMouseX() <= this->_boundX + this->_boundWidth &&
                   this->_window->getMouseY() >= this->_boundY &&
                   this->_window->getMouseY() <= this->_boundY + this->_boundHeight;
        }

        bool Input::wasMouseOver() const {
            return this->_window->wasFocused() && this->_window->getPreviousMouseX() >= this->_boundX &&
                   this->_window->getPreviousMouseX() <= this->_boundX + this->_boundWidth &&
                   this->_window->getPreviousMouseY() >= this->_boundY &&
                   this->_window->getPreviousMouseY() <= this->_boundY + this->_boundHeight;
        }

        int Input::getKeyState(unsigned int keyCode) const {
            return this->_keys[keyCode];
        }

        int Input::getMouseButtonState(unsigned int buttonCode) const {
            return this->_mouseButtons[buttonCode];
        }

        void Input::keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
            Game *game = (Game *) glfwGetWindowUserPointer(window);

            if (!game->getWindow()->isFocused()) {
                return;
            }

            bool isPressed = action != GLFW_RELEASE;
            Input *input = game->getWindow()->getInput();

            if ((!input->_useFocus || input->focused)) {
                for (Listener &listener : input->keyListeners) {
                    if (listener.key == key &&
                        ((listener.state == State::PRESS && !input->_keys[key] && isPressed) ||
                         (listener.state == State::UP && input->_keys[key] && !isPressed))) {
                        listener.handler();
                    }
                }
            }

            input->_keys[key] = isPressed;

            if (game->getActiveScene() != nullptr) {
                input = game->getActiveScene()->getInput();
                input->_keys[key] = isPressed;

                if ((!input->_useFocus || input->focused)) {
                    for (Listener &listener : input->keyListeners) {
                        if (listener.key == key &&
                            ((listener.state == State::PRESS && !input->_keys[key] && isPressed) ||
                             (listener.state == State::UP && input->_keys[key] && !isPressed))) {
                            listener.handler();
                        }
                    }
                }

            }
        }

        void Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
            Game *game = (Game *) glfwGetWindowUserPointer(window);

            if (!game->getWindow()->isFocused()) {
                return;
            }

            bool isPressed = action != GLFW_RELEASE;
            Input* input = game->getWindow()->getInput();

            if (input->isMouseOver()) {
                for (Listener &listener : input->mouseListeners) {
                    if (listener.key == button &&
                        ((listener.state == State::PRESS && !input->_mouseButtons[button] && isPressed) ||
                         (listener.state == State::UP && input->_mouseButtons[button] && !isPressed))) {
                        listener.handler();
                    }
                }
            }

            input->_mouseButtons[button] = isPressed;
            if(game->getActiveScene() != nullptr) {
                input = game->getActiveScene()->getInput();
                input->_mouseButtons[button] = isPressed;

                if (input->isMouseOver()) {
                    for (Listener &listener : input->mouseListeners) {
                        if (listener.key == button &&
                            ((listener.state == State::PRESS && !input->_mouseButtons[button] && isPressed) ||
                             (listener.state == State::UP && input->_mouseButtons[button] && !isPressed))) {
                            listener.handler();
                        }
                    }
                }
            }
        }
    }
}