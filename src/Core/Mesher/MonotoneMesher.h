#include "IMesher.h"
#include "../Structure/Voxel.h"
#include "../Structure/Structure.h"

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
                class MonotonePolygon {
                public:
                    Graphics::Renderer::IRenderer* renderer;
                    std::vector<std::array<int, 2>> left;
                    std::vector<std::array<int, 2>> right;

                    //TODO: Figure out what v, ul and ur are
                    MonotonePolygon(Graphics::Renderer::IRenderer* renderer, int v, int ul, int ur) {
                        this->renderer = renderer;
                        this->left.push_back({ ul, v });
                        this->right.push_back({ ur, v });
                    }

                    void closeOff(int v) {
                        this->left.push_back({this->left[this->left.size() - 1][0], v});
                        this->right.push_back({this->right[this->right.size() - 1][0], v});
                    }

                    void mergeRun(int v, int ul, int ur) {
                        int l = this->left[this->left.size() - 1][0];
                        int r = this->right[this->right.size() - 1][0];

                        if (l != ul) {
                            this->left.push_back({l, v});
                            this->left.push_back({ul, v});
                        }

                        if (r != ur) {
                            this->right.push_back({r, v});
                            this->right.push_back({ur, v});
                        }
                    }
                };

                float _getDimensionFromAxis(int axis, float width, float length, float height);

            public:
                virtual std::vector<MeshPart*> generateMesh(Structure::Structure *structure, float width, float length,
                                                           float height) override;
            };

        }
    }
}

#endif
