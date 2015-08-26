#ifndef CUBICUOUS_MOVABLE_H
#define CUBICUOUS_MOVABLE_H

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <math.h>
#include <glm/detail/func_trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_mat.hpp>

#ifndef M_PI //mingw32 bug work around
#define M_PI 3.14159265358979323846
#endif

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

            virtual glm::mat4 _getRotationMatrix();

        public:
            inline Movable() { };

            inline Movable(glm::vec3 position) {
                this->_initialPosition = position;
                this->_position = position;
            }

            virtual inline void yaw(float yaw) { this->_yaw += yaw; }

            virtual inline void pitch(float pitch) { this->_pitch += pitch; }

            virtual inline void roll(float roll) { this->_roll += roll; }

            virtual inline void setYaw(float yaw) { this->_yaw = yaw; };

            virtual inline void setPitch(float pitch) { this->_pitch = pitch; };

            virtual inline void setRoll(float roll) { this->_roll = roll; };

            virtual inline void setPosition(glm::vec3 position) { this->_position = position; }

            virtual inline float getYaw() const { return _yaw; }

            virtual inline float getPitch() const { return _pitch; }

            virtual inline float getRoll() const { return _roll; }

            virtual const inline glm::vec3& getInitialPosition() const { return _initialPosition; }

            virtual const inline glm::vec3& getPosition() const { return _position; }

            virtual void stride(float by);

            virtual void strafe(float by);

            virtual void climb(float by);

            virtual void mouseLook(float deltaX, float deltaY, float mouseSpeed);
        };
    }
}

#endif
