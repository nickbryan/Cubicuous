#ifndef CUBICUOUS_INPUT_H
#define CUBICUOUS_INPUT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Debugging/Logger.h"

namespace Cubicuous {
    namespace Window {

        #define MAX_KEYS 1024
        #define MAX_MOUSE_BUTTONS 32

        class Input {
        private:
            bool keys[MAX_KEYS];
            bool mouseButtons[MAX_MOUSE_BUTTONS];

            double mouseX;
            double mouseY;

            GLFWwindow *glfwWindow;

        public:
            Input(GLFWwindow *windowPointer);
            ~Input();

            bool isKeyPressed(unsigned int keyCode) const;
            bool isMouseButtonPressed(unsigned int buttonCode) const;

            inline int getMouseX() const { return this->mouseX; }
            inline int getMouseY() const { return this->mouseY; }
            inline void resetMousePosition() const { glfwSetCursorPos(this->glfwWindow, 0.0f, 0.0f); };

            void updateMousePosition();

        private:
            static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

            static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        };

    }
}


#endif
