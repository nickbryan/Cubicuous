#ifndef CUBICUOUS_CUBEENTITY_H
#define CUBICUOUS_CUBEENTITY_H

#include "../../src/Core/Entity.h"

using namespace Cubicuous::Core;

class CubeEntity : public Entity {

public:
    CubeEntity(glm::vec3 position, Cubicuous::Game* game) : Entity(game) {
        this->setPosition(position);
        this->setYaw(0.0f);
        this->setPitch(0.0f);
        this->setRoll(0.0f);
    }

    inline virtual void render(double deltaTime) override {
        this->_game->getMatrixManager()->updateModel(this->getModelMatrix());
        glDrawArrays(GL_TRIANGLES, 0, 36);
    };
};

#endif