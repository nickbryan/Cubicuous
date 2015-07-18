#include "../Game.h"

namespace Cubicuous {
    namespace Core {
        Entity::Entity(Game* game) {
            this->_game = game;
        }

        glm::mat4 Entity::_getRotationMatrix() {
            glm::mat4 rotationMatrix(1.0f);
            // X rotation for pitch
            glm::vec3 pitchAxisRotation;
            if(this->getYaw() > 0.0f && this->getPitch() > 0.0f) {
                pitchAxisRotation.x = 1.0f;
                pitchAxisRotation.z = 1.0f;
            }
            else if(this->getYaw() > 0.0f) {
                pitchAxisRotation.z = 1.0f;
            }
            else {
                pitchAxisRotation.x = 1.0f;
            }

            rotationMatrix = glm::rotate(rotationMatrix, this->getPitch(), pitchAxisRotation);
            // Y rotation for yaw
            rotationMatrix = glm::rotate(rotationMatrix, this->getYaw(), glm::vec3(0.0f, 1.0f, 0.0f));
            // rotation for roll
            rotationMatrix = glm::rotate(rotationMatrix, this->getRoll(), glm::vec3(0.0f, 0.0f, 1.0f));

            return rotationMatrix;
        }
    }
}