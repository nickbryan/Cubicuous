#ifndef CUBICUOUS_VOXEL_H
#define CUBICUOUS_VOXEL_H

#include "../../Graphics/Renderable.h"
#include "../Movable.h"
#include "../Entity.h"

namespace Cubicuous {
    namespace Core {
        namespace Structure {
            class Voxel : public Entity {
            private:
                glm::vec3 _size;

            public:
                inline Voxel(Game *game, glm::vec3 position, glm::vec3 size, Graphics::Renderer::IRenderer* renderer) : _size(size), Entity(game, position, renderer) { }

                inline Voxel(Game *game, glm::vec3 position, Graphics::Renderer::IRenderer* renderer) : Voxel(game, position, glm::vec3(1.0f, 1.0f, 1.0f), renderer) { }

                inline Voxel(Game *game, glm::vec3 position, glm::vec3 size) : _size(size), Entity(game, position) { }

                inline Voxel(Game *game, glm::vec3 position) : Voxel(game, position, glm::vec3(1.0f, 1.0f, 1.0f)) { }

                inline Voxel(Game *game) : Entity(game) {}

                inline Voxel(Game *game, int type) : Entity(game) {}

                inline glm::vec3 getSize() const {
                    return this->_size;
                }
            };
        }
    }
}
#endif