#ifndef CUBICUOUS_WINDOW_H
#define CUBICUOUS_WINDOW_H

#include "../Debugging/Logger.h"
#include "Input.h"

namespace Cubicuous {
    namespace Window {
        struct WindowSettings {
            const char *title;
            int width;
            int height;

            WindowSettings(const char *title, int width, int height) {
                this->title = title;
                this->width = width;
                this->height = height;
            }

            WindowSettings(std::string title, int width, int height) : WindowSettings(title.c_str(), width, height) { }
        };

        class Input;

        class Window {
        public:
            static int OPENGL_VERSION_MAJOR;
            static int OPENGL_VERSION_MINOR;
            static int OPENGL_VERSION_REV;

        private:
            double _mouseX;
            double _mouseY;
            double _previousMouseX;
            double _previousMouseY;

            const char *_title;

            int _width;
            int _height;

            bool _focused = GL_TRUE;
            bool _wasFocused = GL_TRUE;
            bool _cursorLocked = false;

            GLFWwindow* _window = nullptr;
            Input* _input = nullptr;

        public:
            Window(const char *title, int width, int height);

            Window(WindowSettings settings) : Window(settings.title, settings.width, settings.height) { };

            ~Window();

            bool isOpen() const;

            inline bool isCursorLocked() const { return this->_cursorLocked; }

            inline int getWidth() const { return this->_width; }

            inline int getHeight() const { return this->_height; }

            inline GLFWwindow *getWindow() const { return this->_window; }

            inline Input *getInput() const { return this->_input; };

            void clear() const;

            void close() const;

            void update();

            void postRender();

            /**
             * Whether or not the window was focused last frame
             */
            inline bool wasFocused() const { return this->_wasFocused; }

            inline bool isFocused() const { return this->_focused; }

            inline double getMouseX() const { return this->_mouseX; }

            inline double getMouseY() const { return this->_mouseY; }

            inline double getMouseXDiff() const { return this->_mouseX - this->_previousMouseX; }

            inline double getMouseYDiff() const { return this->_mouseY - this->_previousMouseY; }

            inline double getPreviousMouseX() const { return this->_previousMouseX; }

            inline double getPreviousMouseY() const { return this->_previousMouseY; }

            void resetMousePosition();

            void lockCursor();

            void unlockCursor();

        private:
            void _init();

            void _updateMousePosition();

            static void _windowResizeCallback(GLFWwindow *window, int width, int height);

            static void _windowFocusCallback(GLFWwindow *window, int focused);
        };
    }
}
#endif