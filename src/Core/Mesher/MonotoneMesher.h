#include "IMesher.h"

#ifndef CUBICUOUS_MONOTONEMESHER_H
#define CUBICUOUS_MONOTONEMESHER_H

namespace Cubicuous {
    namespace Core {
        namespace Mesher {

            class MonotoneMesher : public IMesher {
            private:
                struct monotonePolygon {
                    int color;
                    int left;
                    int right;

                    monotonePolygon(int color, int v, int ul, int ur) {
                        this->color = color;
                        this->left = [[ul, v]];
                        this->right = [[ur, v]];
                    }
                };

            public:
                virtual void generateMesh(Structure::Structure structure, int dimensions[3]);
            };

        }
    }
}

#endif
