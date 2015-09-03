#ifndef CUBICUOUS_MESHPART_H
#define CUBICUOUS_MESHPART_H

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <array>

namespace Cubicuous {
    namespace Core {
        namespace Mesher {
            class MeshPart {
            private:
                int       _type;
                glm::vec3 _verticies[3];

            public:
                MeshPart(int type) : _type(type) {}

                MeshPart(int type, glm::vec3 verticies[3]) : _type(type), _verticies(verticies) {}

                void setVertex(int position, glm::vec3 vertex) {
                    this->_verticies[position] = vertex;
                }

                int getType() const { return this->_type; }

                glm::vec3* getVerticies() const { return this->_verticies; }
            };
        }
    }
}

#endif