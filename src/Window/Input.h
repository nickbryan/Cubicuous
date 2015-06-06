#ifndef CUBICUOUS_INPUT_H
#define CUBICUOUS_INPUT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Debugging/Logger.h"
#include "Window.h"

namespace Cubicuous {
    namespace Window {
        class Window;

        #define MAX_KEYS 1024
        #define MAX_MOUSE_BUTTONS 32

        class Input {
            public:
                bool focused = false;

            private:
                int _keys[MAX_KEYS];
                int _mouseButtons[MAX_MOUSE_BUTTONS];
                bool _useFocus = false;

                float _boundX;
                float _boundY;
                int   _boundWidth;
                int   _boundHeight;

                Window *_window;

            public:
                Input(Window *windowPointer, bool useFocus, float x, float y, int width, int height);
                Input(Window *windowPointer, float x, float y, int width, int height);
                Input(Window *windowPointer, bool useFocus);
                Input(Window *windowPointer);

                ~Input();

                int getKeyState(unsigned int keyCode) const;
                int getMouseButtonState(unsigned int buttonCode) const;

                bool isKeyPressed(unsigned int keyCode) const;
                bool isMouseButtonPressed(unsigned int buttonCode) const;
                bool isMouseOver() const;
                inline bool isUsingFocus() const { return this->_useFocus; };

            private:
                static void _keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);

                static void _mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        };
    }
}
#endif