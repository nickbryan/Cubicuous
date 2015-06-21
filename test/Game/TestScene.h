#ifndef CUBICUOUS_TESTSCENE_H
#define CUBICUOUS_TESTSCENE_H

#include "../../src/core/Scene.h"
#include "../../src/core/Entity.h"
#include "../../src/Game.h"

class TestScene : public Cubicuous::Core::Scene {
private:
    GLfloat _cube[117] = {
            // back
            -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f,

            // front
            -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f,

            // left
            -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f,

            // right
            0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f,

            // bottom
            -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f,

            // top
            -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f
    };

    GLfloat _color[108] = {
            0.583f, 0.771f, 0.014f, 0.583f, 0.771f, 0.014f, 0.583f, 0.771f, 0.014f,

            0.583f, 0.771f, 0.014f, 0.583f, 0.771f, 0.014f, 0.583f, 0.771f, 0.014f,

            0.597f, 0.770f, 0.761f, 0.597f, 0.770f, 0.761f, 0.597f, 0.770f, 0.761f,

            0.597f, 0.770f, 0.761f, 0.597f, 0.770f, 0.761f, 0.597f, 0.770f, 0.761f,

            0.014f, 0.184f, 0.576f, 0.014f, 0.184f, 0.576f, 0.014f, 0.184f, 0.576f,

            0.014f, 0.184f, 0.576f, 0.014f, 0.184f, 0.576f, 0.014f, 0.184f, 0.576f,

            0.997f, 0.513f, 0.064f, 0.997f, 0.513f, 0.064f, 0.997f, 0.513f, 0.064f,

            0.997f, 0.513f, 0.064f, 0.997f, 0.513f, 0.064f, 0.997f, 0.513f, 0.064f,

            0.055f, 0.953f, 0.042f, 0.055f, 0.953f, 0.042f, 0.055f, 0.953f, 0.042f,

            0.055f, 0.953f, 0.042f, 0.055f, 0.953f, 0.042f, 0.055f, 0.953f, 0.042f,

            0.517f, 0.713f, 0.338f, 0.517f, 0.713f, 0.338f, 0.517f, 0.713f, 0.338f,

            0.517f, 0.713f, 0.338f, 0.517f, 0.713f, 0.338f, 0.517f, 0.713f, 0.338f
    };

public:
    inline TestScene(Cubicuous::Game* game) : Scene(game) {
        game->getVertexBuffer("cubeBuffer").updateData(this->_cube);
        game->getVertexBuffer("colorBuffer").updateData(this->_color);
    };

    void render(double deltaTime) override;

    void update() override;
};

#endif