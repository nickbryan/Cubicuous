#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <GL/glew.h>
#include "TestScene.h"

void TestScene::render(double deltaTime) {
    Cubicuous::Graphics::ShaderProgram *shaderProgram = this->_game->getShaderProgram();
    shaderProgram->enable();
    shaderProgram->setVertexAttribArray("position", 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    this->_cubeBuffer.updateData(this->_cube);

    shaderProgram->setUniformMat4("projection", glm::perspective(glm::radians(45.0f), ((float)800 / (float)600), 1.0f, 10.0f));
    shaderProgram->setUniformMat4("view", glm::lookAt(
            glm::vec3(1.5f, 1.5f, 1.5f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
    ));
    shaderProgram->setUniformMat4("model", glm::mat4(1.0f));

    glDrawArrays(GL_TRIANGLES, 0, 36);
    shaderProgram->disableVertexAttribArray(); //SEGFAULT
}

void TestScene::update() {

}