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

    Cubicuous::Graphics::Uniform* _viewUni;
    Cubicuous::Graphics::Uniform* _projUni;
    Cubicuous::Graphics::Uniform* _modelUni;

    Cubicuous::Graphics::VertexBuffer* _cubeBuffer;
    Cubicuous::Graphics::VertexBuffer* _colorBuffer;
    Cubicuous::Graphics::VertexArray*  _positionVertexArray;
    Cubicuous::Graphics::VertexArray*  _colorVertexArray;

    Cubicuous::Core::Camera *_camera;

public:
    inline TestScene(Cubicuous::Game* game) : Scene(game) {
        this->_viewUni = this->_game->getShaderProgram()->getCachedUniform("view");
        this->_projUni = this->_game->getShaderProgram()->getCachedUniform("projection");
        this->_modelUni = this->_game->getShaderProgram()->getCachedUniform("model");
        this->_colorBuffer = this->_game->getVertexBuffer("colorBuffer");
        this->_cubeBuffer = this->_game->getVertexBuffer("cubeBuffer");
        this->_positionVertexArray = this->_game->getShaderProgram()->getVertexArray("position");
        this->_colorVertexArray = this->_game->getShaderProgram()->getVertexArray("color");
        this->_camera = new Cubicuous::Core::Camera(45.0f, 800.0f / 600.0f,
                                                    1.0f, 100.0f, glm::vec3(0.0f, 0.0f, 5.0f));

        Cubicuous::Debugging::Logger::log("Found attribute position as " + Cubicuous::Debugging::Logger::toLoggable(this->_positionVertexArray->getID()));
        Cubicuous::Debugging::Logger::log("Found attribute color as " + Cubicuous::Debugging::Logger::toLoggable(this->_colorVertexArray->getID()));

        if(this->_viewUni == nullptr) {
            throw "Failed to find view uniform from cache";
        }
        if(this->_projUni == nullptr) {
            throw "Failed to find projection uniform from cache";
        }
        else if(this->_modelUni == nullptr) {
            throw "Failed to find model uniform from cache";
        }

        for(int i = 0; i < 108; i++) {
            this->_cubeColor[i] = 1.0f;
            this->_coloredCube[i] = i < 18 ? this->_coloredCubeColor : 1.0f;
        }

        this->_cubeBuffer->update(this->_cube, 108);
        this->_positionVertexArray->enable();
    };

    void render(double deltaTime) override;

    void update() override;
};

#endif