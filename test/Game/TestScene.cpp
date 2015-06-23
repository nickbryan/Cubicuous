#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <GL/glew.h>
#include "TestScene.h"

void TestScene::render(double deltaTime) {
    Cubicuous::Graphics::ShaderProgram *shaderProgram = this->_game->getShaderProgram();
    this->_cubeBuffer->updateData(this->_cube);

    shaderProgram->setUniformMat4("view", glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::inverse(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 3.0f))));
    shaderProgram->setUniformMat4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f));
    shaderProgram->setUniformMat4("model", glm::mat4(1.0f));

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TestScene::update() {

}