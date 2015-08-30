#include "Structure.h"
#include "../../Game.h"
#include "Voxel.h"

namespace Cubicuous {
    namespace Core {
        namespace Structure {
            void Structure::render(double deltaTime) {
                for(Voxel* voxel : this->getVoxels()) {
                    voxel->render(deltaTime);
                }
            }

            void Structure::addVoxel(glm::vec3 position) {
                this->addVoxel(new Voxel(this->_game, position));
            }

            void Structure::addVoxel(Voxel *voxel) {
                this->_voxels.push_back(voxel);
            }

            void Structure::removeVoxel(Voxel *voxel) {
                this->_voxels.erase(this->_voxels.begin() + this->getVoxelIndex(voxel));
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

            int Structure::getVoxelIndex(const glm::vec3 position) const {
                int index = 0;

                for(Voxel* voxel : this->getVoxels()) {
                    if(voxel->getPosition() == position) {
                        return index;
                    }

                    index++;
                }

                return -1;
            }

            int Structure::getVoxelIndex(Voxel *voxel) const {
                return this->getVoxelIndex(voxel->getPosition());
            }

            void Structure::_buildMesh() {

            }
        }
    }
}