#ifndef CUBICUOUS_MESHPART_H
#define CUBICUOUS_MESHPART_H

#include <GL/glew.h>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <array>

namespace Cubicuous {
    namespace Core {
        namespace Mesher {
            class MeshPart {
            private:
                int       _type;
                glm::vec3 *_vertices;

            public:
                MeshPart(int type) : _type(type) {}

                MeshPart(int type, glm::vec3 *vertices) : _type(type), _vertices(vertices) {}

                void setVertex(int position, glm::vec3 vertex) {
                    this->_vertices[position] = vertex;
                }

                int getType() const { return this->_type; }

                glm::vec3* getVertices() const { return this->_vertices; }

                GLfloat * getVerticesAsFloats() const {
                    GLfloat* floats = new GLfloat[9];
                    int currentFloatIndex = -1;

                    for(int floatIndex = 0; floatIndex < 3; floatIndex++) {
                        floats[++currentFloatIndex] = this->_vertices[floatIndex].x;
                        floats[++currentFloatIndex] = this->_vertices[floatIndex].y;
                        floats[++currentFloatIndex] = this->_vertices[floatIndex].z;
                    }

                    return floats;
                }
            };
        }
    }
}

#endif