#include <glm/glm.hpp>
#include <GL/glew.h>
#include "TestScene.h"

void TestScene::render(double deltaTime) {
    for (Cubicuous::Core::Entity *entity : this->_entities) {
        if(entity == this->_entities[1]) {
            this->_colorBuffer->update(this->_coloredCube, 108);
        }
        else {
            this->_colorBuffer->update(this->_cubeColor, 108);
        }
        this->_game->getShaderProgram()->setActiveVertexArray("color");

        this->_modelUni->update(entity->getModelMatrix());
        this->_game->getShaderProgram()->setActiveVertexArray("position");
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void TestScene::update() {
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
    if (this->_input->isKeyPressed(GLFW_KEY_Z)) {
        this->_camera->climb(0.1f);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_X)) {
        this->_camera->climb(-1 * 0.1f);
    }

    if (this->_input->isKeyPressed(GLFW_KEY_I)) {
        this->_entities[1]->stride(0.1f);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_K)) {
        this->_entities[1]->stride(-1 * 0.1f);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_L)) {
        this->_entities[1]->strafe(0.1f);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_J)) {
        this->_entities[1]->strafe(-1 * 0.1f);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_N)) {
        this->_entities[1]->climb(0.1f);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_M)) {
        this->_entities[1]->climb(-1 * 0.1f);
    }

    if (this->_input->isKeyPressed(GLFW_KEY_1)) {
        std::cout << "Locked to entity" << std::endl;
        this->_camera->lockToEntity(this->_entities[2]);
    }
    if (this->_input->isKeyPressed(GLFW_KEY_2)) {
        std::cout << "Unlocked from entity" << std::endl;
        this->_camera->unlockFromEntity();
    }

    this->_camera->mouseLook((float)this->_game->getWindow()->getMouseXDiff(),
                             (float)this->_game->getWindow()->getMouseYDiff(), 0.001f);
}