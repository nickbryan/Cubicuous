#ifndef CUBICUOUS_ENTITY_H
#define CUBICUOUS_ENTITY_H

#include "Movable.h"
#include "../Graphics/Renderable.h"

namespace Cubicuous {
    class Game;
    namespace Core {
        class Entity : public Movable, public Graphics::Renderable {
        protected:
            Game* _game = nullptr;

            virtual glm::mat4 _getRotationMatrix();

        public:
            inline Entity(Game *game) : _game(game) {};

            inline Entity(Game *game, glm::vec3 position) : _game(game), Movable(position) {};

            inline virtual void update() {}

            inline virtual glm::mat4 getModelMatrix() {
                return glm::translate(glm::mat4(), this->getPosition()) * this->_getRotationMatrix();
            }
        };
    }
}
#endif