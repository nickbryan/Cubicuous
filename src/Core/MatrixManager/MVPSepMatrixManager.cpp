#include "MVPSepMatrixManager.h"

namespace Cubicuous {
    namespace Core {
        namespace MatrixManager {
            void MVPSepMatrixManager::updateModel(glm::mat4 model) {
                this->_modelUni->update(model);
            }

            void MVPSepMatrixManager::updateProjection(glm::mat4 projection) {
                this->_projUni->update(projection);
            }

            void MVPSepMatrixManager::updateView(glm::mat4 view) {
                this->_viewUni->update(view);
            }
        }
    }
}