#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <GL/glew.h>
#include "TestScene.h"

void TestScene::render(double deltaTime) {
    this->_viewUni->update(glm::lookAt(
            glm::vec3(1.5f, 1.5f, 1.5f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
    ));
    this->_projUni->update(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f));
    this->_modelUni->update(glm::mat4(1.0f));

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TestScene::update() {
    std::cout << "Current fps " << this->_game->getSettings()->loop->getFps() << std::endl;
}