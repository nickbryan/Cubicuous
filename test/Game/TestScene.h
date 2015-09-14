#ifndef CUBICUOUS_TESTSCENE_H
#define CUBICUOUS_TESTSCENE_H

#include "../../src/core/Scene.h"
#include "../../src/core/Entity.h"
#include "../../src/Game.h"
#include "../../src/Core/Camera.h"

class TestScene : public Cubicuous::Core::Scene {
private:
    GLfloat _coloredCubeColor = 0.5f;
    GLfloat _coloredCube[108];
    GLfloat _cubeColor[108];

    GLfloat _cube[108] = {//X, Y, Z
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
    };

    Cubicuous::Graphics::VertexArray*  _positionVertexArray;
    Cubicuous::Graphics::VertexArray*  _colorVertexArray;

public:
    inline TestScene(Cubicuous::Game* game) : Scene(game) {
        this->_positionVertexArray = this->_game->getShaderProgram()->getVertexArray("vertices");
        this->_colorVertexArray = this->_game->getShaderProgram()->getVertexArray("color");
        this->setCamera(new Cubicuous::Core::Camera(game, 45.0f, 800.0f / 600.0f,
                                                    1.0f, 100.0f, glm::vec3(0.0f, 0.0f, 5.0f)));

        for(int i = 0; i < 108; i++) {
            this->_cubeColor[i] = 1.0f;
            this->_coloredCube[i] = i < 18 ? this->_coloredCubeColor : 1.0f;
        }

        this->_game->getGeometryManager()->updateVertices(this->_cube, 108);
        this->_positionVertexArray->enable();
    };

    void render(double deltaTime) override;

    void update() override;
};

#endif