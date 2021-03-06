#include "../Game.h"

namespace Cubicuous {
    namespace Core {

        Camera::Camera(Game *game, float fieldOfView, float aspectRatio, float nearPlane, float farPlane, glm::vec3 position) {
            this->_game = game;
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

        void Camera::lockToEntity(Entity* entity) {
            this->unlockFromEntity();
            this->_entity = entity;
        }

        void Camera::unlockFromEntity() {
            if (!this->isLockedToEntity()) {
                return;
            }

            this->_pitch = -this->_entity->getPitch();
            this->_roll = -this->_entity->getRoll();
            this->_yaw = -this->_entity->getYaw();
            this->_position = this->_entity->getPosition();
            this->_entity = nullptr;
        }

        const glm::vec3& Camera::getPosition() const {
            if (this->isLockedToEntity()) {
                return this->getLockedEntity()->getPosition();
            }

            return Movable::getPosition();
        }

        float Camera::getYaw() const {
            if (this->isLockedToEntity()) {
                return -this->getLockedEntity()->getYaw();
            }

            return Movable::getYaw();
        }

        float Camera::getPitch() const {
            if (this->isLockedToEntity()) {
                return -this->getLockedEntity()->getPitch();
            }

            return Movable::getPitch();
        }

        float Camera::getRoll() const {
            if (this->isLockedToEntity()) {
                return -this->getLockedEntity()->getRoll();
            }

            return Movable::getRoll();
        }

        void Camera::setYaw(float yaw) {
            if (this->isLockedToEntity()) {
                this->getLockedEntity()->setYaw(-yaw);
            }

            Movable::setYaw(yaw);
        }

        void Camera::setPitch(float pitch) {
            if (this->isLockedToEntity()) {
                this->getLockedEntity()->setPitch(-pitch);
            }

            Movable::setPitch(pitch);
        }

        void Camera::setRoll(float roll) {
            if (this->isLockedToEntity()) {
                this->getLockedEntity()->setRoll(-roll);
            }

            Movable::setRoll(roll);
        }

        void Camera::setPosition(glm::vec3 position) {
            if (this->isLockedToEntity()) {
                this->getLockedEntity()->setPosition(position);
            }

            Movable::setPosition(position);
        }

        void Camera::updateMVP() {
            this->_game->getMatrixManager()->updateView(this->getViewMatrix());
            this->_game->getMatrixManager()->updateProjection(this->getProjectionMatrix());
        }

        glm::mat4 Camera::getViewMatrix() {
            return this->_getRotationMatrix() * glm::inverse(glm::translate(glm::mat4(), this->getPosition()));
        }
    }
}