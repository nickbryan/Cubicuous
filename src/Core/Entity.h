#ifndef CUBICUOUS_ENTITY_H
#define CUBICUOUS_ENTITY_H

#include "Movable.h"

namespace Cubicuous {
    class Game;
    namespace Core {
        class Entity : public Movable {
        protected:
            Game* _game;

            virtual glm::mat4 _getRotationMatrix();

        public:
            Entity(Game *game);

            inline virtual void render(double deltaTime) {};

            inline virtual void update() {};

            inline glm::mat4 getModelMatrix() {
                return glm::translate(glm::mat4(), this->getPosition()) * this->_getRotationMatrix();
            }
        };
    }
}
#endif