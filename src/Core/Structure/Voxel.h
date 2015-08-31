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
                int _type = 0;

            public:
                inline Voxel(Game *game, glm::vec3 position, int type) : _type(type), Entity(game, position) { }
            
                inline Voxel(Game *game, glm::vec3 position) : Entity(game, position) { }

                inline Voxel(Game *game) : Entity(game) {}

                inline Voxel(Game *game, int type) : _type(type), Entity(game) {}

                inline virtual void render(double deltaTime) override {
                    //TODO: Make sure the cube position data is active here, add cube position data to engine its self
                    this->_game->getMatrixManager()->updateModel(this->getModelMatrix());
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                };

                inline virtual int getType() const { return this->_type; }
            };
        }
    }
}
#endif