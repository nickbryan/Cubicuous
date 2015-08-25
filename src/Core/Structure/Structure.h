#ifndef CUBICUOUS_BLOCK_H
#define CUBICUOUS_BLOCK_H

#include <vector>
#include <glm/detail/type_vec.hpp>
#include "Voxel.h"
#include "../Entity.h"
#include <GL/glew.h>

namespace Cubicuous {
    namespace Core {
        namespace Structure {
            class Structure : public Entity {
            private:
                glm::mat4 _mesh;

            public:
                inline Structure(Game *game, const std::vector<Voxel *> &_voxels) : Entity(game), _voxels(_voxels) { }

                void addVoxel(Voxel *voxel);

                void addVoxel(glm::vec3 position);

                inline void setVoxels(std::vector<Voxel*> voxels) {
                    this->_voxels = voxels;
                    this->_buildMesh();
                }

                void removeVoxel(Voxel *voxel);

                void removeVoxel(glm::vec3 position);

                Voxel* getVoxel(const glm::vec3 position) const;

                inline std::vector<Voxel*> getVoxels() const { return this->_voxels; }

                int getVoxelIndex(const glm::vec3 position) const;

                int getVoxelIndex(Voxel* voxel) const { return this->getVoxelIndex(voxel->getPosition()); };

                //TODO: Implement this method, render the mesh mat4, build if not built
                virtual void render(double deltaTime) override;

            private:
                //TODO: Implement this method to make one mat4 from all voxel vec3
                void _buildMesh();

                std::vector<Voxel*> _voxels;
            };
        }
    }
}
#endif