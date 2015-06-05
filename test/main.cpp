#include "../src/Window/Window.h"

int main() {

    Cubicuous::Window::Window window("Cubicuous", 800, 600);

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGl Version Supported: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;

    while (window.isOpen()) {
        window.clear();

        window.update();
    }

    return 0;
}