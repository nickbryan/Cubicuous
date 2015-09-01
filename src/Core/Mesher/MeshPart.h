#ifndef CUBICUOUS_MESHPART_H
#define CUBICUOUS_MESHPART_H

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>

namespace Cubicuous {
    namespace Core {
        namespace Mesher {
            class MeshPart {
            private:
                int       _type;
                glm::vec3 _position;

            public:
                MeshPart(int type, glm::vec3 position) : _type(type), _position(position) {}

                int getType() const { return this->_type; }

                glm::vec3 getPosition() const { return this->_position; }
            };
        }
    }
}

#endif