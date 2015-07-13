#ifndef CUBICUOUS_TESTSCENE_H
#define CUBICUOUS_TESTSCENE_H

#include "../../src/core/Scene.h"
#include "../../src/core/Entity.h"
#include "../../src/Game.h"
#include "../../src/Core/Camera.h"

class TestScene : public Cubicuous::Core::Scene {
private:
    GLfloat _coloredCube[108] = {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
    };

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

    Cubicuous::Graphics::VertexBuffer* _colorBuffer;

    Cubicuous::Core::Camera *_camera;

public:
    inline TestScene(Cubicuous::Game* game) : Scene(game) {
        this->_game->getVertexBuffer("cubeBuffer")->update(this->_cube, 108);
        this->_viewUni = this->_game->getShaderProgram()->getCachedUniform("view");
        this->_projUni = this->_game->getShaderProgram()->getCachedUniform("projection");
        this->_modelUni = this->_game->getShaderProgram()->getCachedUniform("model");
        this->_colorBuffer = this->_game->getVertexBuffer("colorBuffer");
        this->_camera = new Cubicuous::Core::Camera(45.0f, 800.0f / 600.0f,
                                                    1.0f, 100.0f, glm::vec3(0.0f, 0.0f, 5.0f));

        if(this->_viewUni == nullptr) {
            throw "Failed to find view uniform from cache";
        }
        if(this->_projUni == nullptr) {
            throw "Failed to find projection uniform from cache";
        }
        else if(this->_modelUni == nullptr) {
            throw "Failed to find model uniform from cache";
        }

        this->_viewUni->update(this->_camera->getViewMatrix());
        this->_projUni->update(this->_camera->getProjectionMatrix());

        for(int i = 0; i < 108; i++) {
            this->_cubeColor[i] = 0.0f;
        }
    };

    void render(double deltaTime) override;

    void update() override;
};

#endif