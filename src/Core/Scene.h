#ifndef CUBICUOUS_SCENE_H
#define CUBICUOUS_SCENE_H

#include <vector>
#include "Entity.h"

namespace Cubicuous {
    class Game;

    namespace Core {
        class Scene {
        protected:
            std::vector<Entity> _entities;

        public:
            inline Scene() {};
            inline ~Scene() {};

            virtual inline void addEntity(Entity entity) {
                this->_entities.push_back(entity);
            }

            //scene used methods
            virtual void render(Cubicuous::Game *game, double deltaTime) {
                for (Entity entity : this->_entities) {
                    entity.render(deltaTime);
                }
            }

            virtual void update(Cubicuous::Game *game) {
                for (Entity entity : this->_entities) {
                    entity.update();
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