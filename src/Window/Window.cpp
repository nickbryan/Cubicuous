#include <stdlib.h>
#include "Window.h"
#include "Exception.h"
#include "../Game.h"

namespace Cubicuous {
    namespace Window {
        int Window::OPENGL_VERSION_MAJOR = 3;
        int Window::OPENGL_VERSION_MINOR = 3;
        int Window::OPENGL_VERSION_REV = 0;

        Window::Window(const char *title, int width, int height) {
            this->_title = title;
            this->_width = width;
            this->_height = height;
            this->_init();
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

        void Window::_init() {
            if (!glfwInit()) {
                throw Exception("Failed to initialise GLFW!");
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
            if (!this->_window) {
                throw Exception("Failed to create GLFW window!");
            }

            glfwMakeContextCurrent(this->_window);

            int major;
            int minor;
            glGetIntegerv(GL_MAJOR_VERSION, &major);
            glGetIntegerv(GL_MINOR_VERSION, &minor);

            if(major < Window::OPENGL_VERSION_MAJOR) {
                throw Exception("OpenGL major installation version (" + Debugging::Logger::toLoggable(major) + ") too old!");
            }
            else if(minor < Window::OPENGL_VERSION_MINOR) {
                throw Exception("OpenGL minor installation version (" + Debugging::Logger::toLoggable(minor) + ") too old!");
            }

            // Initialise the input handler, this needs to be read only
            this->_input = new Input(this);

            //event listeners
            glfwSetWindowSizeCallback(this->_window, Window::_windowResizeCallback);
            glfwSetWindowFocusCallback(this->_window, Window::_windowFocusCallback);

            glewExperimental = GL_TRUE;
            if (glewInit() != GLEW_OK) {
                throw Exception("Failed to initialise GLEW!");
            }

            glGetError(); // GLEW can randomly raise 1280 when you hint for opengl 3.3, ignore it as it's a bug in GLEW
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_MULTISAMPLE);

            #ifdef _WIN32
                glEnableClientState(GL_VERTEX_ARRAY);
            #endif

            glViewport(0, 0, this->_width, this->_height);
        }

        bool Window::isOpen() const {
            return !glfwWindowShouldClose(this->_window);
        }

        void Window::update() {
            this->_wasFocused = this->_focused;
            this->_updateMousePosition();
            this->_input->processEvents();
            glfwPollEvents();
        }

        void Window::postRender() {
            glfwSwapBuffers(this->_window);
        }

        void Window::_windowResizeCallback(GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        }

        void Window::_windowFocusCallback(GLFWwindow *window, int focused) {
            Game *game = (Game *) glfwGetWindowUserPointer(window);
            game->getWindow()->_focused = focused == GL_TRUE;
        }

        void Window::_updateMousePosition() {
            this->_previousMouseX = this->_mouseX;
            this->_previousMouseY = this->_mouseY;
            glfwGetCursorPos(this->_window, &this->_mouseX, &this->_mouseY);
        }

        void Window::resetMousePosition() {
            glfwSetCursorPos(this->_window, 0.0f, 0.0f);
            this->_mouseX = 0;
            this->_mouseY = 0;
            this->_previousMouseX = 0;
            this->_previousMouseY = 0;
        }

        void Window::unlockCursor() {
            if(this->_cursorLocked) {
                glfwSetInputMode(this->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }

        void Window::lockCursor() {
            if(!this->_cursorLocked) {
                glfwSetInputMode(this->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }
    }
}