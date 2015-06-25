#ifndef CUBICUOUS_ENTITY_H
#define CUBICUOUS_ENTITY_H

namespace Cubicuous {
    namespace Core {
        class Entity {
        public:
            inline virtual void render(double deltaTime) {};

            inline virtual void update() {};
        };
    }
}
#endif