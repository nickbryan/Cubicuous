#ifndef CUBICUOUS_IMATRIXMANAGER_H
#define CUBICUOUS_IMATRIXMANAGER_H

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>

namespace Cubicuous {
    namespace Core {
        namespace MatrixManager {
            class IMatrixManager {
            public:
                virtual void updateModel(glm::mat4 model) { };

                virtual void updateProjection(glm::mat4 projection) { };

                virtual void updateView(glm::mat4 view) { };
            };
        }
    }
}
#endif