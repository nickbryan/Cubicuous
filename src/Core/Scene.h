#ifndef CUBICUOUS_SCENE_H
#define CUBICUOUS_SCENE_H

#include <vector>
#include "Entity.h"

namespace Cubicuous {
    namespace Core {
        class Scene {
        protected:
	        std::vector<Entity> _entities;

        public:
	        virtual inline void addEntity(Entity entity) {
		        this->_entities.push_back(entity);
	        }

	        //scene used methods
	        virtual void render(long deltaTime) {
		        for (Entity entity : this->_entities) {
			        entity.render(deltaTime);
		        }
	        }

	        virtual void update(long deltaTime) {
		        for (Entity entity : this->_entities) {
			        entity.update(deltaTime);
		        }
	        }

	        //events
	        virtual void onActive() { };

	        virtual void onInactive() { };

	        virtual void onPause() { };

	        virtual void onPlay() { };
        };
    }
}
#endif