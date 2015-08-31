#ifndef CUBICUOUS_BLOCK_H
#define CUBICUOUS_BLOCK_H

#include <vector>
#include <glm/detail/type_vec.hpp>
#include "../Entity.h"
#include "../Mesher/MeshPart.h"
#include <GL/glew.h>
#include <array>

namespace Cubicuous {
    namespace Core {
        namespace Structure {
            class Voxel;
            class Structure : public Entity {
            private:
                std::array<Mesher::MeshPart> _mesh;

                //TODO: Implement this method to make one mat4 from all voxel vec3
                void _buildMesh();

                std::vector<Voxel*> _voxels;

            public:
                inline Structure(Game *game, const std::vector<Voxel *> &_voxels) : Entity(game), _voxels(_voxels) { }

                inline Structure(Game *game) : Entity(game), _voxels(std::vector<Voxel*>()) {}

                void addVoxel(Voxel *voxel);

                void addVoxel(glm::vec3 position);

                inline void setVoxels(std::vector<Voxel*> voxels) {
                    this->_voxels = voxels;
                    this->_buildMesh();
                }

                void removeVoxel(Voxel *voxel);

                void removeVoxel(glm::vec3 position);

                Voxel* getVoxel(float x, float y, float z) const;

                inline Voxel* getVoxel(const glm::vec3 position) const { return this->getVoxel(position.x, position.y, position.z) };

                inline std::vector<Voxel*> getVoxels() const { return this->_voxels; }

                int getVoxelIndex(const glm::vec3 position) const;

                int getVoxelIndex(Voxel* voxel) const;

                //TODO: Implement this method, render the mesh mat4, build if not built
                virtual void render(double deltaTime) override;
            };
        }
    }
}
#endif