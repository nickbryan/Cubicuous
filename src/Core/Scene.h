#ifndef CUBICUOUS_SCENE_H
#define CUBICUOUS_SCENE_H

#include <vector>
#include "Entity.h"
#include "../Window/Input.h"

using Cubicuous::Window::Input;

namespace Cubicuous {
    class Game;

    namespace Core {
        class Scene {
        protected:
            std::vector<Entity*> _entities;
            Cubicuous::Game* _game;
            Input *_input;

        public:
            Scene(Cubicuous::Game* game);
            virtual inline ~Scene() {
                if(this->_input != nullptr) {
                    delete(this->_input);
                }
            };

            virtual inline Input* getInput() const { return this->_input; }

            virtual void addEntity(Entity* entity);

            //scene used methods
            virtual void render(double deltaTime);

            virtual void update();

            //events
            virtual void onActive() { };

            virtual void onInactive() { };

            virtual void onPause() { };

            virtual void onPlay() { };
        };
    }
}
#endif