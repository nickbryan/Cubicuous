#ifndef CUBICUOUS_ENTITY_H
#define CUBICUOUS_ENTITY_H

#include "Movable.h"
#include "../Graphics/Renderable.h"
#include "../Graphics/Renderer/IRenderer.h"

namespace Cubicuous {
    class Game;
    namespace Core {
        class Entity : public Movable, public Graphics::Renderable {
        protected:
            Game* _game = nullptr;

            Graphics::Renderer::IRenderer *_renderer = nullptr;

            virtual glm::mat4 _getRotationMatrix();

        public:
            inline Entity(Game *game) : _game(game) {};

            inline Entity(Game *game, glm::vec3 position) : _game(game), Movable(position) {};

            inline Entity(Game *game, glm::vec3 position, Graphics::Renderer::IRenderer* renderer) : _game(game), _renderer(renderer), Movable(position) {};

            inline virtual void update() {}

            inline Graphics::Renderer::IRenderer* getRenderer() const {
                return this->_renderer;
            }

            inline virtual glm::mat4 getModelMatrix() {
                return glm::translate(glm::mat4(), this->getPosition()) * this->_getRotationMatrix();
            }
        };
    }
}
#endif