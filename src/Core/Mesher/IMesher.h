#ifndef CUBICUOUS_IMESHER_H
#define CUBICUOUS_IMESHER_H

#include <vector>
#include "../Structure/Structure.h"
#include "MeshPart.h"

namespace Cubicuous {
    namespace Core {
        namespace Mesher {
            class IMesher {
            public:
                virtual std::vector<MeshPart*> generateMesh(Structure::Structure *structure, float width, float length,
                                                           float height) = 0;
            };

        }
    }
}

#endif
