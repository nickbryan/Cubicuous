#ifndef CUBICUOUS_CAMERA_H
#define CUBICUOUS_CAMERA_H

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_mat.hpp>

namespace Cubicuous {
    namespace Core {
        class Camera {
        private:
            float _fieldOfView;
            float _aspectRatio;
            float _nearPlane;
            float _farPlabe;

            float _yaw;
            float _pitch;
            float _roll;

            glm::mat4 _projection;

            glm::vec3 _initialPosition;
            glm::vec3 _position;
            glm::vec3 _view;
            glm::vec3 _right;
            glm::vec3 _up;

        public:
            Camera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane, glm::vec3 position);
            ~Camera();

            inline void setYaw(float yaw) { this->_yaw = yaw; };
            inline void setPitch(float pitch) { this->_pitch = pitch; };
            inline void setRoll(float yaw) { this->_yaw = yaw; };
            inline void setPosition(glm::vec3 position) { this->_position = position; }


            void stride(float by);
            void strafe(float by);
            void climb(float by);

            void mouseLook(float deltaX, float deltaY, float mouseSpeed);

            glm::mat4 getViewMatrix();
            glm::mat4 getProjectionMatrix();

        private:
            glm::mat4 _getRotationMatrix();
            glm::vec3 _getViewVector();
            glm::vec3 _getRightVector();
        };
    }
}

#endif
