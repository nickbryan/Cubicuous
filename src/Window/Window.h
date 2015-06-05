#ifndef CUBICUOUS_WINDOW_H
#define CUBICUOUS_WINDOW_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Cubicuous {
    namespace Window {

        class Window {
        private:
            const char *title;

            int width;
            int height;

            GLFWwindow *window;

        public:
            Window(const char *title, int width, int height);
            ~Window();

            bool isOpen() const;

            inline int getWidth()  const { return this->width; }
            inline int getHeight() const { return this->height; }

            void clear() const;
            void close() const;
            void update() const;

        private:
            bool init();

            static void windowResizeCallback(GLFWwindow *window, int width, int height);
        };

    }
}

#endif
