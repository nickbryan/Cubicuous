#include "Movable.h"

namespace Cubicuous {
    namespace Core {
        void Movable::stride(float by) {
            glm::vec3 viewVector = this->_getViewVector();
            glm::vec3 pos = this->getPosition();
            pos.x += viewVector.x * by;
            pos.z += viewVector.z * by;
            this->setPosition(pos);
        }

        void Movable::strafe(float by) {
            glm::vec3 rightVector = this->_getRightVector();
            glm::vec3 pos = this->getPosition();
            pos.x += rightVector.x * by;
            pos.z += rightVector.z * by;
            this->setPosition(pos);
        }

        void Movable::climb(float by) {
            glm::vec3 pos = this->getPosition();
            pos.y += by;
            this->setPosition(pos);
        }

        void Movable::mouseLook(float deltaX, float deltaY, float mouseSpeed) {
            this->setYaw(this->getYaw() + (deltaX * mouseSpeed));
            this->setPitch(this->getPitch() + (deltaY * mouseSpeed));

            // if yaw goes above 360 (2 * PI in radians) set it back to 0 to make it easier to deal with
            if (this->getYaw() > (2 * M_PI)) {
                this->setYaw(0);
            }

            // Ensure yaw is between 0 and 360
            if (this->getYaw() < 0) {
                this->setYaw(2 * M_PI);
            }

            // Dont know what quaternion rotations are so we are going to cap up and donw
            // to 75 +- degrees
            // This stops our orientation from fliping round and stops the "gimbal lock" issue
            if (this->getPitch() > glm::radians(75.0f)) {
                this->setPitch(glm::radians(75.0f));
            }
            else if (this->getPitch() < glm::radians(-75.0f)) {
                this->setPitch(glm::radians(-75.0f));
            }
        }

        glm::mat4 Movable::_getRotationMatrix() {
            glm::mat4 rotationMatrix(1.0f);
            // X rotation for pitch
            rotationMatrix = glm::rotate(rotationMatrix, this->getPitch(), glm::vec3(1.0f, 0.0f, 0.0f));
            // Y rotation for yaw
            rotationMatrix = glm::rotate(rotationMatrix, this->getYaw(), glm::vec3(0.0f, 1.0f, 0.0f));
            // rotation for roll
            rotationMatrix = glm::rotate(rotationMatrix, this->getRoll(), glm::vec3(0.0f, 0.0f, 1.0f));

            return rotationMatrix;
        }

        glm::vec3 Movable::_getViewVector() {
            return glm::vec3(glm::inverse(this->_getRotationMatrix()) * glm::vec4(0, 0, -1, 1));
        }

        glm::vec3 Movable::_getRightVector() {
            return glm::vec3(glm::inverse(this->_getRotationMatrix()) * glm::vec4(1, 0, 0, 1));
        }
    }
}