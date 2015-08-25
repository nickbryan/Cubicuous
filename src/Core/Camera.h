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

            Entity *_entity;
            Game *_game;

        public:
            Camera(Game* game, float fieldOfView, float aspectRatio, float nearPlane, float farPlane, glm::vec3 position);
            ~Camera();

            //Projection settings
            float getFieldOfView() const { return _fieldOfView; }
            float getAspectRatio() const { return _aspectRatio; }
            float getNearPlane() const { return _nearPlane; }
            float getFarPlane() const { return _farPlane; }

            //Entity locking
            void lockToEntity(Entity *entity);

            void unlockFromEntity();

            inline Entity* getLockedEntity() const { return this->_entity; }

            //Camera matrix functions
            glm::mat4 getViewMatrix();

            inline glm::mat4 getProjectionMatrix() const { return this->_projection; }

            //3D position translation and transformation settinsg
            virtual const glm::vec3 &getPosition() const override;

            virtual float getYaw() const override;

            virtual float getPitch() const override;

            virtual float getRoll() const override;

            virtual void setYaw(float yaw) override;

            virtual void setPitch(float pitch) override;

            virtual void setRoll(float roll) override;

            virtual void setPosition(glm::vec3 position) override;

            virtual void updateMVP();
        };
    }
}

#endif
