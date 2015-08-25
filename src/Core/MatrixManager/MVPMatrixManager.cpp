#include "MVPMatrixManager.h"

namespace Cubicuous {
    namespace Core {
        namespace MatrixManager {
            void MVPMatrixManager::updateModel(glm::mat4 model) {
                this->_model = model;
                this->_update();
            }

            void MVPMatrixManager::updateProjection(glm::mat4 projection) {
                this->_projection = projection;
                this->_update();
            }

            void MVPMatrixManager::updateView(glm::mat4 view) {
                this->_view = view;
                this->_update();
            }

            void MVPMatrixManager::_update() {
                this->_mvpUni->update(this->_model * this->_view * this->_projection);
            }
        }
    }
}