#ifndef CUBICUOUS_IMESHER_H
#define CUBICUOUS_IMESHER_H

#include <vector>
#include <array>
#include "../Structure/Structure.h"
#include "MeshPart.h"

namespace Cubicuous {
    namespace Core {
        namespace Mesher {
            class IMesher {
            public:
                virtual std::array<MeshPart> generateMesh(Structure::Structure *structure, int width, int length, int height) = 0;
            };

        }
    }
}

#endif
