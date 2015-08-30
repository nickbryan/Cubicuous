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
                inline Voxel(Game *game, glm::vec3 position) : Entity(game, position) { }

                inline Voxel(Game *game) : Entity(game) {}

                inline virtual void render(double deltaTime) override {
                    this->_game->getMatrixManager()->updateModel(this->getModelMatrix());
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                };
            };
        }
    }
}
#endif