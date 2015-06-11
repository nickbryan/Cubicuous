#include <stdlib.h>
#include "Window.h"

namespace Cubicuous {
    namespace Window {
        int Window::OPENGL_VERSION_MAJOR = 3;
        int Window::OPENGL_VERSION_MINOR = 3;
        int Window::OPENGL_VERSION_REV = 0;

        Window::Window(const char *title, int width, int height) {
            this->_title = title;
            this->_width = width;
            this->_height = height;

            if (!this->_init()) {
                glfwTerminate();
            }
        }

        Window::~Window() {
            glfwTerminate();

            #ifdef _WIN32
                system("PAUSE");
            #endif
        }

        void Window::clear() const {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void Window::close() const {
            glfwSetWindowShouldClose(this->_window, GL_TRUE);
        }

        bool Window::_init() {
            if (!glfwInit()) {
                Debugging::Logger::log("Failed to initialise GLFW!");
                return false;
            }

            // We need this to get latest version of OpenGl on mac
            #ifdef __APPLE__
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Window::OPENGL_VERSION_MAJOR);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Window::OPENGL_VERSION_MINOR);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            #endif

            glfwGetVersion(&Window::OPENGL_VERSION_MAJOR, &Window::OPENGL_VERSION_MINOR, &Window::OPENGL_VERSION_REV);

            this->_window = glfwCreateWindow(this->_width, this->_height, this->_title, nullptr, nullptr);
            if (!_window) {
                Debugging::Logger::log("Failed to create GLFW window!");
                return false;
            }

            glfwMakeContextCurrent(this->_window);

            // Allows us to access our window in our callbacks
            glfwSetWindowUserPointer(this->_window, this);

            // Initialise the input handler, this needs to be read only
            this->_input = new Input(this);

            //event listeners
            glfwSetWindowSizeCallback(this->_window, Window::_windowResizeCallback);
            glfwSetWindowFocusCallback(this->_window, Window::_windowFocusCallback);

            glewExperimental = GL_TRUE;
            if (glewInit() != GLEW_OK) {
                Debugging::Logger::log("Failed to initialise GLEW!");
                return false;
            }

            return true;
        }

        bool Window::isOpen() const {
            return !glfwWindowShouldClose(this->_window);
        }

        void Window::update() {
            this->_wasFocused = this->_focused;
            this->_updateMousePosition();
            this->_input->processEvents();
            glfwSwapBuffers(this->_window);
            glfwPollEvents();
        }

        void Window::_windowResizeCallback(GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        }

        void Window::_windowFocusCallback(GLFWwindow *window, int focused) {
            Window *win = (Window *) glfwGetWindowUserPointer(window);
            win->_focused = focused == GL_TRUE;
        }

        void Window::_updateMousePosition() {
            this->_previousMouseX = this->_mouseX;
            this->_previousMouseY = this->_mouseY;
            glfwGetCursorPos(this->_window, &this->_mouseX, &this->_mouseY);
        }
    }
}