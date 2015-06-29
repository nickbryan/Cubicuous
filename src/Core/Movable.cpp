#include <math.h>
#include <glm/detail/func_trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Movable.h"

namespace Cubicuous {
    namespace Core {
        void Movable::stride(float by) {
            glm::vec3 viewVector = this->_getViewVector();

            this->_position.x += viewVector.x * by;
            this->_position.z += viewVector.z * by;
        }

        void Movable::strafe(float by) {
            glm::vec3 rightVector = this->_getRightVector();

            this->_position.x += rightVector.x * by;
            this->_position.z += rightVector.z * by;
        }

        void Movable::climb(float by) {
            this->_position.y += by;
        }

        void Movable::mouseLook(float deltaX, float deltaY, float mouseSpeed) {
            this->_yaw += deltaX * mouseSpeed;
            this->_pitch += deltaY * mouseSpeed;

            // if yaw goes above 360 (2 * PI in radians) set it back to 0 to make it easier to deal with
            if (this->_yaw > (2 * M_PI)) {
                this->_yaw = 0;
            }

            // Ensure yaw is between 0 and 360
            if (this->_yaw < 0) {
                this->_yaw = (2 * M_PI);
            }

            // Dont know what quaternion rotations are so we are going to cap up and donw
            // to 75 +- degrees
            // This stops our orientation from fliping round and stops the "gimbal lock" issue
            if (this->_pitch > glm::radians(75.0f)) {
                this->_pitch = glm::radians(75.0f);
            }
            if (this->_pitch < glm::radians(-75.0f)) {
                this->_pitch = glm::radians(-75.0f);
            }
        }

        glm::mat4 Movable::_getRotationMatrix() {
            glm::mat4 rotationMatrix(1.0f);
            // X rotation for pitch
            rotationMatrix = glm::rotate(rotationMatrix, this->_pitch, glm::vec3(1.0f, 0.0f, 0.0f));
            // Y rotation for yaw
            rotationMatrix = glm::rotate(rotationMatrix, this->_yaw, glm::vec3(0.0f, 1.0f, 0.0f));
            // rotation for roll
            rotationMatrix = glm::rotate(rotationMatrix, this->_roll, glm::vec3(0.0f, 0.0f, 1.0f));

            return rotationMatrix;
        }

        glm::vec3 Movable::_getViewVector() {
            glm::vec4 viewVector = glm::inverse(this->_getRotationMatrix()) * glm::vec4(0, 0, -1, 1);
            return glm::vec3(viewVector);
        }

        glm::vec3 Movable::_getRightVector() {
            glm::vec4 rightVector = glm::inverse(this->_getRotationMatrix()) * glm::vec4(1, 0, 0, 1);
            return glm::vec3(rightVector);
        }
    }
}