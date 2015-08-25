#include "Structure.h"
#include "../../Game.h"

namespace Cubicuous {
    namespace Core {
        namespace Structure {
            void Structure::render(double deltaTime) {
                
            }

            void Structure::addVoxel(glm::vec3 position) {
                this->addVoxel(new Voxel(this->_game, position));
            }

            void Structure::addVoxel(Voxel *voxel) {
                this->_voxels.push_back(voxel);
            }

            void Structure::removeVoxel(Voxel *voxel) {
                this->_voxels.erase(std::remove(this->_voxels.begin(), this->_voxels.end(), voxel), this->_voxels.end());
            }

            void Structure::removeVoxel(glm::vec3 position) {
                this->removeVoxel(this->getVoxel(position));
            }

            Voxel* Structure::getVoxel(const glm::vec3 position) const {
                for(Voxel* voxel : this->getVoxels()) {
                    if(voxel->getPosition() == position) {
                        return voxel;
                    }
                }

                return nullptr;
            }

            void Structure::_buildMesh() {

            }
        }
    }
}