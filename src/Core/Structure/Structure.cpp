#include "Structure.h"
#include "../../Game.h"
#include "Voxel.h"

namespace Cubicuous {
    namespace Core {
        namespace Structure {
            void Structure::render(double deltaTime) {
                if(this->_game->getMesher() != nullptr) {
                    if(this->_mesh == nullptr) {
                        this->_buildMesh();
                    }
                }
                else {
                    for (Voxel *voxel : this->getVoxels()) {
                        voxel->render(deltaTime);
                    }
                }
            }

            void Structure::addVoxel(glm::vec3 position) {
                this->addVoxel(new Voxel(this->_game, position));
            }

            void Structure::addVoxel(Voxel *voxel) {
                this->_voxels.push_back(voxel);
                this->_buildMesh();
            }

            void Structure::removeVoxel(Voxel *voxel) {
                this->_voxels.erase(this->_voxels.begin() + this->getVoxelIndex(voxel));
                this->_buildMesh();
            }

            void Structure::removeVoxel(glm::vec3 position) {
                this->removeVoxel(this->getVoxel(position));
            }

            Voxel* Structure::getVoxel(float x, float y, float z) const {
                for(Voxel* voxel : this->getVoxels()) {
                    if(voxel->getPosition().x == x && voxel->getPosition().y == y && voxel->getPosition().z == z) {
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
                this->_mesh = this->_game->getMesher()->generateMesh(this, )
            }
        }
    }
}