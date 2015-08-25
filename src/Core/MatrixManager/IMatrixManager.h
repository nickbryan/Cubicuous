#ifndef CUBICUOUS_IMATRIXMANAGER_H
#define CUBICUOUS_IMATRIXMANAGER_H

#include <glm/detail/type_mat.hpp>

namespace Cubicuous {
    namespace Core {
        namespace MatrixManager {
            class IMatrixManager {
            public:
                virtual void updateModel(glm::mat4 model) = 0;

                virtual void updateProjection(glm::mat4 projection) = 0;

                virtual void updateView(glm::mat4 view) = 0;
            };
        }
    }
}
#endif