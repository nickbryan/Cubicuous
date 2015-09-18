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
                std::vector<Mesher::MeshPart*> _mesh;
                GLfloat *_meshVertices;
                int      _totalMeshTriangles;
                bool     _meshGenerationEnabled = true;

                std::vector<Voxel*> _voxels;

                float _width;
                float _length;
                float _height;

                void _recalculateBoundingBox();
                void _meshToVertices();

            public:
                inline Structure(Game *game, const std::vector<Voxel *> &_voxels) : Entity(game), _voxels(_voxels) { }

                inline Structure(Game *game) : Entity(game), _voxels(std::vector<Voxel*>()) {}

                //Voxel management
                void addVoxel(Voxel *voxel);
                void addVoxel(glm::vec3 position, glm::vec3 size);
                void addVoxel(glm::vec3 position);

                inline void setVoxels(std::vector<Voxel*> voxels) {
                    this->_voxels = voxels;
                    this->buildMesh();
                }

                void removeVoxel(Voxel *voxel);
                void removeVoxel(glm::vec3 position);

                Voxel* getVoxel(float x, float y, float z) const;

                inline Voxel* getVoxel(const glm::vec3 position) const { return this->getVoxel(position.x, position.y, position.z); };

                inline std::vector<Voxel*> getVoxels() const { return this->_voxels; }

                int getVoxelIndex(const glm::vec3 position) const;
                int getVoxelIndex(Voxel* voxel) const;

                //Mesh management
                void buildMesh();
                inline void stopMeshGeneration() { this->_meshGenerationEnabled = false; }
                inline void resumeMeshGeneration() { this->_meshGenerationEnabled = true; }
                inline float getWidth() const { return this->_width; }
                inline float getLength() const { return this->_length; }
                inline float getHeight() const { return this->_height; }

                inline std::vector<Mesher::MeshPart*> getMesh() const { return this->_mesh; }
                inline GLfloat* getMeshVertices() const { return this->_meshVertices; }

                //Entity methods
                virtual void render(double deltaTime) override;
            };
        }
    }
}
#endif