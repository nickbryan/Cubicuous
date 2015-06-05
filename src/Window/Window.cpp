#include "Window.h"

namespace Cubicuous {
    namespace Window {

        Window::Window(const char *title, int width, int height)
        {
            this->title = title;
            this->width = width;
            this->height = height;

            if (!this->init()) {
                glfwTerminate();
            }
        }

        Window::~Window()
        {
            glfwTerminate();
        }

        void Window::clear() const
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void Window::close() const
        {
            glfwSetWindowShouldClose(this->window, GL_TRUE);
        }

        bool Window::init()
        {
            if (!glfwInit()) {
                std::cout << "Failed to initialise GLFW!" << std::endl;
                return false;
            }

            // We need this to get latest version of OpenGl on mac
            #ifdef __APPLE__
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            #endif

            this->window = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);
            if (!window) {
                std::cout << "Failed to create GLFW window!" << std::endl;
                return false;
            }

            glfwMakeContextCurrent(this->window);

            glewExperimental = GL_TRUE;
            if (glewInit() != GLEW_OK) {
                std::cout << "Failed to initialise GLEW!" << std::endl;
                return false;
            }

            return true;
        }

        bool Window::isOpen() const
        {
            return !glfwWindowShouldClose(this->window);
        }

        void Window::update() const
        {
            glfwSwapBuffers(this->window);
            glfwPollEvents();
        }

        void Window::windowResizeCallback(GLFWwindow *window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }

    }
}
