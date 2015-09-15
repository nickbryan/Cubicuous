#include "Structure.h"
#include "../../Game.h"
#include "Voxel.h"

namespace Cubicuous {
    namespace Core {
        namespace Structure {
            void Structure::render(double deltaTime) {
                if(this->_game->getMesher() != nullptr) {
                    if(this->_totalMeshTriangles <= 0) {
                        return;
                    }

                    if(this->_game->getGeometryManager()->isVerticesUniformOnly()) {
                        for(Mesher::MeshPart *meshPart : this->getMesh()) {
                            if(meshPart->getRenderer() != nullptr) {
                                meshPart->render();
                            }
                            else {
                                this->_game->getGeometryManager()->updateVertices(meshPart->getVerticesAsFloats(), meshPart->getLastVerticesCount() / 3);
                                glDrawArrays(GL_TRIANGLES, 0, meshPart->getLastVerticesCount() / 3);
                            }
                        }
                    }
                    else {
                        this->_game->getGeometryManager()->updateVertices(this->_meshVertices, this->_totalMeshTriangles);
                        glDrawArrays(GL_TRIANGLES, 0, this->_totalMeshTriangles);
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
                if(!this->_meshGenerationEnabled) {
                    return;
                }

                this->_recalculateBoundingBox();
                this->_mesh = this->_game->getMesher()->generateMesh(this, this->getWidth(), this->getLength(), this->getHeight());
                this->_meshToVertices();
            }

            void Structure::_meshToVertices() {
                this->_totalMeshTriangles = 0;
                this->_meshVertices = new GLfloat[this->getMesh().size() * 3 * 3];
                int verticesBlock = -1;

                for(Mesher::MeshPart *meshPart : this->getMesh()) {
                    for(glm::vec3 vertex : meshPart->getVertices()) {
                        this->_meshVertices[++verticesBlock] = vertex.x;
                        this->_meshVertices[++verticesBlock] = vertex.y;
                        this->_meshVertices[++verticesBlock] = vertex.z;
                    }

                    this->_totalMeshTriangles++;
                }
            }

            void Structure::_recalculateBoundingBox() {
                float minX = 0.0f;
                float minY = 0.0f;
                float minZ = 0.0f;
                float maxX = 0.0f;
                float maxY = 0.0f;
                float maxZ = 0.0f;

                for(Voxel* voxel : this->getVoxels()) {
                    if(voxel->getPosition().x < minX) {
                        minX = voxel->getPosition().x;
                    }
                    if(voxel->getPosition().y < minY) {
                        minY = voxel->getPosition().y;
                    }
                    if(voxel->getPosition().z < minZ) {
                        minZ = voxel->getPosition().z;
                    }
                    if(voxel->getPosition().x > maxX) {
                        maxX = voxel->getPosition().x;
                    }
                    if(voxel->getPosition().y > minY) {
                        maxY = voxel->getPosition().y;
                    }
                    if(voxel->getPosition().z > minZ) {
                        maxZ = voxel->getPosition().z;
                    }
                }

                this->_width = maxX - minX;
                this->_height = maxY - minY;
                this->_length = maxZ - minZ;
            }
        }
    }
}