#ifndef CUBICUOUS_WINDOW_H
#define CUBICUOUS_WINDOW_H

#include "../Debugging/Logger.h"
#include "Input.h"

namespace Cubicuous {
    namespace Window {
        class Window {
        friend class Input;

        private:
	        const char *title;

	        int width;
	        int height;

	        GLFWwindow *window;

        public:
            static int OPENGL_VERSION_MAJOR;
            static int OPENGL_VERSION_MINOR;
            static int OPENGL_VERSION_REV;

            Input *input;

        private:
            bool init();

            static void windowResizeCallback(GLFWwindow *window, int width, int height);

        public:
	        Window(const char *title, int width, int height);

	        ~Window();

	        bool isOpen() const;

	        inline int getWidth() const { return this->width; }

	        inline int getHeight() const { return this->height; }

			inline GLFWwindow* getWindowPointer() const { return this->window; }

	        void clear() const;

	        void close() const;

	        void update() const;
        };
    }
}
#endif