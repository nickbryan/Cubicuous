#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <GL/glew.h>
#include "TestScene.h"
#include "../../src/Graphics/ShaderProgram.h"

void TestScene::render(double deltaTime) {
    Cubicuous::Graphics::ShaderProgram *shaderProgram = this->_game->getShaderProgram();

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), ((float)800 / (float)600), 1.0f, 10.0f);

    glm::mat4 viewMatrix = glm::lookAt(
            glm::vec3(1.5f, 1.5f, 1.5f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
    );

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

    shaderProgram->setUniformMat4("mvp", mvpMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TestScene::update() {

}