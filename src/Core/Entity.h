#ifndef CUBICUOUS_ENTITY_H
#define CUBICUOUS_ENTITY_H

#include "Movable.h"

namespace Cubicuous {
    namespace Core {
        class Entity : public Movable {
        public:
            inline virtual void render(double deltaTime) {};

            inline virtual void update() {};

            inline glm::mat4 getModelMatrix() {
                return this->_getRotationMatrix() * glm::translate(glm::mat4(), this->getPosition());
            }
        };
    }
}
#endif