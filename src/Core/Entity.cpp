#include "../Game.h"

namespace Cubicuous {
    namespace Core {
        Entity::Entity(Game* game) {
            this->_game = game;
        }

        glm::mat4 Entity::_getRotationMatrix() {
            glm::mat4 rotationMatrix(1.0f);

            // Z rotation for roll
            rotationMatrix = glm::rotate(rotationMatrix, this->getRoll(), glm::vec3(0.0f, 0.0f, 1.0f));
            // Y rotation for yaw
            rotationMatrix = glm::rotate(rotationMatrix, this->getYaw(), glm::vec3(0.0f, 1.0f, 0.0f));
            // X rotation for pitch
            rotationMatrix = glm::rotate(rotationMatrix, this->getPitch(), glm::vec3(1.0f, 0.0f, 0.0f));


            return rotationMatrix;
        }
    }
}