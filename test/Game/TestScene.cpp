#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <GL/glew.h>
#include "TestScene.h"

void TestScene::render(double deltaTime) {
    if (this->_input->isKeyPressed(GLFW_KEY_W)) {
        this->_camera->stride(0.1f);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_S)) {
        this->_camera->stride(-1 * 0.1f);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_D)) {
        this->_camera->strafe(0.1f);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_A)) {
        this->_camera->strafe(-1 * 0.1f);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_X)) {
        this->_camera->climb(0.1f);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_Z)) {
        this->_camera->climb(-1 * 0.1f);
    }

    double mouseX;
    double mouseY;
    glfwGetCursorPos(this->_game->getWindow()->getWindow(), &mouseX, &mouseY);

    this->_camera->mouseLook((float)mouseX, (float)mouseY, 0.001f);

    this->_viewUni->update(this->_camera->getViewMatrix());
    this->_projUni->update(this->_camera->getProjectionMatrix());
    this->_modelUni->update(glm::mat4(1.0f));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glfwSetCursorPos(this->_game->getWindow()->getWindow(), 0, 0);
}

void TestScene::update() {
    std::cout << "Current fps " << this->_game->getSettings()->loop->getFps() << std::endl;
}