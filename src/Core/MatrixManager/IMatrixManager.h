#ifndef CUBICUOUS_MATRIXMANAGER_H
#define CUBICUOUS_MATRIXMANAGER_H

#include "../../Game.h"

namespace Cubicuous {
    namespace Core {
        namespace MatrixManager {
            class IMatrixManager {
            public:
                virtual void updateModel(glm::mat4 model);

                virtual void updateProjection(glm::mat4 projection);

                virtual void updateView(glm::mat4 view);
            };
        }
    }
}
#endif