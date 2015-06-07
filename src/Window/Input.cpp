#include "Input.h"

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

            for (int i =0; i < MAX_MOUSE_BUTTONS; i++) {
                this->_mouseButtons[i] = false;
            }

            glfwSetCursorPos(this->_window->getWindow(), 0.0f, 0.0f);
            glfwSetKeyCallback(this->_window->getWindow(), this->_keyCallback);
            glfwSetMouseButtonCallback(this->_window->getWindow(), this->_mouseButtonCallback);
        }

        Input::Input(Window *windowPointer, float x, float y, int width, int height) :
               Input(windowPointer, false, x, y, width, height) { }

        Input::Input(Window *windowPointer, bool useFocus) :
               Input(windowPointer, useFocus, 0, 0, windowPointer->getWidth(), windowPointer->getHeight()) { }

        Input::Input(Window *windowPointer) : Input(windowPointer, false) { }

        Input::~Input() {
            delete(&this->_keys);
            delete(&this->_mouseButtons);
            delete(&this->_boundX);
            delete(&this->_boundY);
            delete(&this->_boundWidth);
            delete(&this->_boundHeight);
        }

        void Input::processEvents() {
            if(!this->_window->isFocused()) {
                return;
            }

	        /* Key events */
	        for(Listener &listener : this->keyListeners) {
		        if(this->_keys[listener.key] && listener.state == State::DOWN) {
			        listener.handler();
		        }
	        }

	        /* Mouse events */
	        if(this->isMouseOver()) {
		        if(!this->wasMouseOver()) {
			        for(auto& listener : this->mouseEnterListeners) {
				        listener();
			        }
		        }

		        if(this->_window->getPreviousMouseX() != this->_window->getMouseX() || this->_window->getPreviousMouseY() != this->_window->getMouseY()) {
			        for(auto& listener : this->mouseMoveListeners) {
				        listener();
			        }
		        }

		        for(Listener &listener : this->mouseListeners) {
			        if(this->_mouseButtons[listener.key] && listener.state == State::DOWN) {
			            listener.handler();
			        }
		        }
	        }
	        else if(this->wasMouseOver()) {
	            for(auto& listener : this->mouseLeaveListeners) {
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
            return this->_window->isFocused() &&
                   this->_window->getMouseX() >= this->_boundX &&
                   this->_window->getMouseX() <= this->_boundX + this->_boundWidth &&
                   this->_window->getMouseY() >= this->_boundY &&
                   this->_window->getMouseY() <= this->_boundY + this->_boundHeight;
        }

        bool Input::wasMouseOver() const {
	        return this->_window->wasFocused() &&
	               this->_window->getPreviousMouseX() >= this->_boundX &&
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

        void Input::_keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
            Window *win = (Window*)glfwGetWindowUserPointer(window);

            if(!win->isFocused()) {
                return;
            }

	        bool isPressed = action != GLFW_RELEASE;
	        if((!win->_input->_useFocus || win->_input->focused)) {
		        for (Listener &listener : win->_input->keyListeners) {
			        if (listener.key == key &&
			            ((listener.state == State::PRESS && !win->_input->_keys[key] && isPressed) || (listener.state == State::UP && win->_input->_keys[key] && !isPressed))) {
				        listener.handler();
			        }
		        }
	        }

	        win->_input->_keys[key] = isPressed;
        }

        void Input::_mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
            Window *win = (Window*)glfwGetWindowUserPointer(window);

	        if(!win->isFocused()) {
		        return;
	        }

	        bool isPressed = action != GLFW_RELEASE;
	        if(win->_input->isMouseOver()) {
		        for (Listener &listener : win->_input->mouseListeners) {
			        if (listener.key == button &&
			            (
			                (listener.state == State::PRESS && !win->_input->_mouseButtons[button] && isPressed) ||
			                (listener.state == State::UP && win->_input->_mouseButtons[button] && !isPressed)
			            )
		            ) {
				        listener.handler();
			        }
		        }
	        }

	        win->_input->_mouseButtons[button] = isPressed;
        }
    }
}