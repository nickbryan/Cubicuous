#ifndef CUBICUOUS_TESTSCENE_H
#define CUBICUOUS_TESTSCENE_H

#include "../../src/core/Scene.h"
#include "../../src/core/Entity.h"
#include "../../src/Game.h"

class TestScene : public Cubicuous::Core::Scene {
private:
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

    Cubicuous::Graphics::Uniform* _viewUni;
    Cubicuous::Graphics::Uniform* _projUni;
    Cubicuous::Graphics::Uniform* _modelUni;

public:
    inline TestScene(Cubicuous::Game* game) : Scene(game) {
        this->_game->getVertexBuffer("cubeBuffer")->updateData(this->_cube, 108);
        this->_viewUni = this->_game->getShaderProgram()->getCachedUniform("view");
        this->_projUni = this->_game->getShaderProgram()->getCachedUniform("projection");
        this->_modelUni = this->_game->getShaderProgram()->getCachedUniform("model");

        if(this->_viewUni == nullptr) {
            throw "Failed to find view uniform from cache";
        }
        if(this->_projUni == nullptr) {
            throw "Failed to find projection uniform from cache";
        }
        else if(this->_modelUni == nullptr) {
            throw "Failed to find model uniform from cache";
        }
    };

    void render(double deltaTime) override;

    void update() override;
};

#endif