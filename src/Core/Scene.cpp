#include "Scene.h"
#include "../Game.h"

namespace Cubicuous {
    namespace Core {
        Scene::Scene(Cubicuous::Game* game) {
            this->_game = game;
            this->_input = new Cubicuous::Window::Input(game->getWindow());
        }

        void Scene::addEntity(Entity* entity) {
            this->_entities.push_back(entity);
        }

        void Scene::render(double deltaTime) {
            for (Entity* entity : this->_entities) {
                entity->render(deltaTime);
            }
        }

        void Scene::update() {
            for (Entity* entity : this->_entities) {
                entity->update();
            }
        }
    }
}
