#include "Input.h"
#include "Window.h"

namespace Cubicuous {
    namespace Window {

        Input::Input(GLFWwindow *windowPointer) {
            this->glfwWindow = windowPointer;

            for (int i = 0; i < MAX_KEYS; i++) {
                this->keys[i] = false;
            }

            for (int i =0; i < MAX_MOUSE_BUTTONS; i++) {
                this->mouseButtons[i] = false;
            }

            glfwSetCursorPos(this->glfwWindow, 0.0f, 0.0f);

            glfwSetKeyCallback(this->glfwWindow, this->keyCallback);
            glfwSetMouseButtonCallback(this->glfwWindow, this->mouseButtonCallback);
        }

        Input::~Input() {
            // ...
        }

        bool Input::isKeyPressed(unsigned int keyCode) const {
            if (keyCode > MAX_KEYS) {
                Debugging::Logger::log("Key pressed is not in our key range!");
                return false;
            }

            return this->keys[keyCode];
        }

        bool Input::isMouseButtonPressed(unsigned int buttonCode) const {
            if (buttonCode > MAX_MOUSE_BUTTONS) {
                Debugging::Logger::log("Mouse button pressed is not in our button range!");
                return false;
            }

            return this->mouseButtons[buttonCode];
        }

        void Input::updateMousePosition() {
            glfwGetCursorPos(this->glfwWindow, &this->mouseX, &this->mouseY);
        }

        void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
            Window *win = (Window*)glfwGetWindowUserPointer(window);
            win->input->keys[key] = action != GLFW_RELEASE;
        }

        void Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
            Window *win = (Window*)glfwGetWindowUserPointer(window);
            win->input->mouseButtons[button] = action != GLFW_RELEASE;
        }

    }
}
