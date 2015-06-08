#ifndef CUBICUOUS_ENTITY_H
#define CUBICUOUS_ENTITY_H

namespace Cubicuous {
    namespace Core {
        class Entity {
        public:
	        virtual void render(long deltaTime);

	        virtual void update(long deltaTime);
        };
    }
}
#endif