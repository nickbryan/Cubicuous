#ifndef CUBICUOUS_IMESHER_H
#define CUBICUOUS_IMESHER_H

#include <vector>
#include "../Structure/Structure.h"

namespace Cubicuous {
    namespace Core {
        namespace Mesher {

            class IMesher {
            public:
                virtual void generateMesh(Structure::Structure structure, int dimensions[3]) = 0;
            };

        }
    }
}

#endif
