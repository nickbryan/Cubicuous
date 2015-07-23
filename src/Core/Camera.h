#ifndef CUBICUOUS_CAMERA_H
#define CUBICUOUS_CAMERA_H

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <cmath>
#include <iostream>
#include "Movable.h"
#include "Entity.h"

namespace Cubicuous {
    namespace Core {
        class Camera : public Movable {
        private:
            float _fieldOfView;
            float _aspectRatio;
            float _nearPlane;
            float _farPlane;

            glm::mat4 _projection;

            Entity *_entity = nullptr;

        public:
            Camera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane, glm::vec3 position);
            ~Camera();

            float getFieldOfView() const { return _fieldOfView; }
            float getAspectRatio() const { return _aspectRatio; }
            float getNearPlane() const { return _nearPlane; }
            float getFarPlane() const { return _farPlane; }

            inline void lockToEntity(Entity *entity) {
                this->_entity = entity;
            }

            inline void unlockFromEntity() {
                if (this->_entity == nullptr) {
                    return;
                }

                this->_pitch = -this->_entity->getPitch();
                this->_roll = -this->_entity->getRoll();
                this->_yaw = -this->_entity->getYaw();
                this->_position = this->_entity->getPosition();
                this->_entity = nullptr;
            }

            inline Entity* getLockedEntity() const { return this->_entity; }

            glm::mat4 getViewMatrix();

            virtual const inline glm::vec3 &getPosition() const override {
                if (this->_entity != nullptr) {
                    return _entity->getPosition();
                }

                return Movable::getPosition();
            }

            virtual inline float getYaw() const override {
                if (this->_entity != nullptr) {
                    return -_entity->getYaw();
                }

                return Movable::getYaw();
            }

            virtual inline float getPitch() const override {
                if (this->_entity != nullptr) {
                    return -_entity->getPitch();
                }

                return Movable::getPitch();
            }

            virtual inline float getRoll() const override {
                if (this->_entity != nullptr) {
                    return -_entity->getRoll();
                }

                return Movable::getRoll();
            }

            virtual inline void setYaw(float yaw) override {
                if (this->_entity != nullptr) {
                    this->_entity->setYaw(-yaw);
                }

                Movable::setYaw(yaw);
            }

            virtual inline void setPitch(float pitch) override {
                if (this->_entity != nullptr) {
                    this->_entity->setPitch(-pitch);
                }

                Movable::setPitch(pitch);
            }

            virtual inline void setRoll(float roll) override {
                if (this->_entity != nullptr) {
                    this->_entity->setRoll(-roll);
                }

                Movable::setRoll(roll);
            }

            virtual inline void setPosition(glm::vec3 position) override {
                if (this->_entity != nullptr) {
                    this->_entity->setPosition(position);
                }

                Movable::setPosition(position);
            }

            inline glm::mat4 getProjectionMatrix() const {
                return this->_projection;
            }
        };
    }
}

#endif
