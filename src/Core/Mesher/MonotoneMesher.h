#include "IMesher.h"

#ifndef CUBICUOUS_MONOTONEMESHER_H
#define CUBICUOUS_MONOTONEMESHER_H

namespace Cubicuous {
    namespace Core {
        namespace Mesher {

            /**
             * Implementation of polygon triangulation to create
             * a monotone mesh of vectors for rendering.
             * Thanks mikolalysenko for the algorithm
             *
             * @see https://github.com/mikolalysenko/mikolalysenko.github.com/blob/master/MinecraftMeshes2/js/monotone.js
            */
            class MonotoneMesher : public IMesher {
            private:
                struct MonotonePolygon {
                    int color;
                    int left[2][2];
                    int right[2][2];

                    //TODO: Figure out what v, ul and ur are
                    MonotonePolygon(int color, int v, int ul, int ur) {
                        this->color = color;
                        this->left[0][0] = ul;
                        this->left[0][1] = v;
                        this->right[0][0] = ur;
                        this->right[0][1] = v;
                    }
                };

                Structure::Voxel* _getVoxelFromPosition(Structure::Structure *structure, int width, int length, int height, float x, float y, float z);

                int _getDimensionFromAxis(int axis, int width, int length, int height);

            public:
                virtual void generateMesh(Structure::Structure* structure, int width, int length, int height) override;
            };

        }
    }
}

#endif
