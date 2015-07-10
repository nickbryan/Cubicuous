#include <glm/detail/func_trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

namespace Cubicuous {
    namespace Core {

        Camera::Camera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane, glm::vec3 position) {
            this->_fieldOfView = fieldOfView;
            this->_aspectRatio = aspectRatio;
            this->_nearPlane = nearPlane;
            this->_farPlane = farPlane;
            this->_position = position;
            this->_initialPosition = position;
            this->_yaw = 0.0f;
            this->_pitch = 0.0f;
            this->_roll = 0.0f;

            this->_projection = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
        }

        Camera::~Camera() {

        }

        glm::mat4 Camera::getViewMatrix() {
            return this->_getRotationMatrix() * glm::inverse(glm::translate(glm::mat4(), this->getPosition()));
        }

        void Camera::stride(float by) {
            if(this->_entity != nullptr) {
                this->_entity->stride(by);
            } else {
                Movable::stride(by);
            }
        }

        void Camera::strafe(float by) {
            if(this->_entity != nullptr) {
                this->_entity->strafe(by);
            } else {
                Movable::strafe(by);
            }
        }

        void Camera::climb(float by) {
            if(this->_entity != nullptr) {
                this->_entity->climb(by);
            } else {
                Movable::climb(by);
            }
        }
    }
}
