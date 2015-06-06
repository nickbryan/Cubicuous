#ifndef CUBICUOUS_WINDOW_H
#define CUBICUOUS_WINDOW_H

#include "../Debugging/Logger.h"
#include "Input.h"

namespace Cubicuous {
    namespace Window {
        class Input;

        class Window {
            friend class Input;

            public:
                static int OPENGL_VERSION_MAJOR;
                static int OPENGL_VERSION_MINOR;
                static int OPENGL_VERSION_REV;

            private:
                double _mouseX;
                double _mouseY;

                const char *_title;

                int _width;
                int _height;

                GLFWwindow *_window;
                Input *_input;

            public:
                Window(const char *title, int width, int height);

                ~Window();

                bool isOpen() const;

                inline int getWidth() const { return this->_width; }

                inline int getHeight() const { return this->_height; }

                inline GLFWwindow* getWindow() const { return this->_window; }

                inline Input* getInput() const { return this->_input; };

                void clear() const;

                void close() const;

                void update();

                inline double getMouseX() const { return this->_mouseX; }
                inline double getMouseY() const { return this->_mouseY; }
                inline void   resetMousePosition() const { glfwSetCursorPos(this->_window, 0.0f, 0.0f); };

            private:
                bool _init();

                void _updateMousePosition();

                static void _windowResizeCallback(GLFWwindow *window, int width, int height);
        };
    }
}
#endif