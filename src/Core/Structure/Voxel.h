#ifndef CUBICUOUS_VOXEL_H
#define CUBICUOUS_VOXEL_H

#include "../../Graphics/Renderable.h"
#include "../Movable.h"
#include "../Entity.h"

namespace Cubicuous {
    namespace Core {
        namespace Structure {
            class Voxel : public Entity {
            public:
                inline Voxel(Game *game, glm::vec3 position, Graphics::Renderer::IRenderer* renderer) : Entity(game, position, renderer) { }

                inline Voxel(Game *game, glm::vec3 position) : Entity(game, position) { }

                inline Voxel(Game *game) : Entity(game) {}

                inline Voxel(Game *game, int type) : Entity(game) {}
            };
        }
    }
}
#endif