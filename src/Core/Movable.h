#ifndef CUBICUOUS_MOVABLE_H
#define CUBICUOUS_MOVABLE_H

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>

namespace Cubicuous {
    namespace Core {
        class Movable {
        private:
            glm::vec3 _getViewVector();
            glm::vec3 _getRightVector();

        protected:
            float _yaw;
            float _pitch;
            float _roll;

            glm::vec3 _initialPosition;
            glm::vec3 _position;

            glm::mat4 _getRotationMatrix();

        public:
            virtual inline void setYaw(float yaw) { this->_yaw = yaw; };
            virtual inline void setPitch(float pitch) { this->_pitch = pitch; };
            virtual inline void setRoll(float roll) { this->_roll = roll; };
            virtual inline void setPosition(glm::vec3 position) { this->_position = position; }

            virtual inline float getYaw() const { return _yaw; }
            virtual inline float getPitch() const { return _pitch; }
            virtual inline float getRoll() const { return _roll; }

            virtual const inline glm::vec3 &getInitialPosition() const { return _initialPosition; }
            virtual const inline glm::vec3 &getPosition() const { return _position; }

            void stride(float by);
            void strafe(float by);
            void climb(float by);

            void mouseLook(float deltaX, float deltaY, float mouseSpeed);
        };
    }
}

#endif
