#include "Window.h"

namespace Cubicuous {
    namespace Window {
        int Window::OPENGL_VERSION_MAJOR = 3;
        int Window::OPENGL_VERSION_MINOR = 3;
        int Window::OPENGL_VERSION_REV = 0;

        Window::Window(const char *title, int width, int height) {
	        this->title = title;
	        this->width = width;
	        this->height = height;

	        if (!this->init()) {
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
	        glfwSetWindowShouldClose(this->window, GL_TRUE);
        }

        bool Window::init() {
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

	        this->window = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);
	        if (!window) {
		        Debugging::Logger::log("Failed to create GLFW window!");
		        return false;
	        }

	        glfwMakeContextCurrent(this->window);

            // Allows us to access our window in our callbacks
            glfwSetWindowUserPointer(this->window, this);

            // Initialise the input handler, this needs to be read only
            this->input = new Input(this->window);

	        glewExperimental = GL_TRUE;
	        if (glewInit() != GLEW_OK) {
		        Debugging::Logger::log("Failed to initialise GLEW!");
		        return false;
	        }

	        return true;
        }

        bool Window::isOpen() const {
	        return !glfwWindowShouldClose(this->window);
        }

        void Window::update() const {
            this->input->updateMousePosition();
	        glfwSwapBuffers(this->window);
	        glfwPollEvents();
        }



        void Window::windowResizeCallback(GLFWwindow *window, int width, int height) {
	        glViewport(0, 0, width, height);
        }
    }
}