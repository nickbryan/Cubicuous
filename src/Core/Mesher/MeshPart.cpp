#include "MeshPart.h"
#include "../../Graphics/Renderer/IRenderer.h"

namespace Cubicuous {
    namespace Core {
        namespace Mesher {
            GLfloat* MeshPart::getVerticesAsFloats() {
                GLfloat* floats = new GLfloat[9];
                this->_floatCount = -1;

                for(int floatIndex = 0; floatIndex < 3; floatIndex++) {
                    floats[++this->_floatCount] = this->_vertices[floatIndex].x;
                    floats[++this->_floatCount] = this->_vertices[floatIndex].y;
                    floats[++this->_floatCount] = this->_vertices[floatIndex].z;
                }

                return floats;
            }

            void MeshPart::render() {
                this->getRenderer()->render(this->getVerticesAsFloats(), this->_floatCount);
            }
        }
    }
}