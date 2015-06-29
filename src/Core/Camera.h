#ifndef CUBICUOUS_CAMERA_H
#define CUBICUOUS_CAMERA_H

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <cmath>
#include "Movable.h"

#ifndef M_PI //mingw32 bug work around
#define M_PI 3.14159265358979323846
#endif

namespace Cubicuous {
    namespace Core {
        class Camera : public Movable {
        private:
            float _fieldOfView;
            float _aspectRatio;
            float _nearPlane;
            float _farPlane;

            glm::mat4 _projection;

            glm::vec3 _view;
            glm::vec3 _right;
            glm::vec3 _up;

        public:
            Camera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane, glm::vec3 position);
            ~Camera();

            float getFieldOfView() const { return _fieldOfView; }
            float getAspectRatio() const { return _aspectRatio; }
            float getNearPlane() const { return _nearPlane; }
            float getFarPlane() const { return _farPlane; }

            glm::mat4 getViewMatrix();
            glm::mat4 getProjectionMatrix();
        };
    }
}

#endif
