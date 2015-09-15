#ifndef CUBICUOUS_COLORRENDERER_H
#define CUBICUOUS_COLORRENDERER_H

#include <glm/detail/type_vec4.hpp>
#include "IRenderer.h"

namespace Cubicuous {
    namespace Graphics {
        namespace Renderer {
            class ColorRenderer : public IRenderer {
            private:
                glm::vec4 _color;

            public:
                ColorRenderer(Game* game, glm::vec4 color) : _color(color), IRenderer(game) { }

                ColorRenderer(Game* game, glm::vec3 color) : _color(glm::vec4(color.x, color.y, color.z, 1.0f)), IRenderer(game) { }

                glm::vec4 getColor() const {
                    return this->_color;
                }

                virtual void render(GLfloat* vertices, GLsizei size) override;

                virtual bool isSameAs(IRenderer* renderer) override;
            };
        }
    }
}

#endif