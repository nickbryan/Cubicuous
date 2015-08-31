#ifndef CUBICUOUS_MESHPART_H
#define CUBICUOUS_MESHPART_H

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>

namespace Cubicuous {
    namespace Core {
        namespace Mesher {
            struct MeshPart {
            public:
                int color;
                glm::vec3 position;
            };
        }
    }
}

#endif