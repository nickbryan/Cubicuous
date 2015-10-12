#include "ColorRenderer.h"
#include "../../Game.h"

namespace Cubicuous {
    namespace Graphics {
        namespace Renderer {
            void ColorRenderer::render(GLfloat* vertices, GLsizei size) {
                this->_game->getGeometryManager()->updateColor(this->_color, size);
                this->_game->getGeometryManager()->updateVertices(vertices, size);
            }

            bool ColorRenderer::isSameAs(IRenderer* renderer) const {
                if(dynamic_cast<ColorRenderer*>(renderer) == 0) {
                    return false;
                }

                return this->_color == dynamic_cast<ColorRenderer*>(renderer)->getColor();
            }
        }
    }
}
