#include "MonotoneMesher.h"

namespace Cubicuous {
    namespace Core {
        namespace Mesher {

            void MonotoneMesher::generateMesh(Structure::Structure structure, int dimensions[3]) {
                //vertices array
                //faces array
                int f(int i, int j, int k) {
                    //return volume[i + dims[0] * (j + dims[1] * k)];
                    return 0;
                }

                // We need to go over the axis x,y and z
                for (int axis = 0; axis < 3; ++axis) {
                    int structureXPosition, struxtureYPosition, structureZPosition;
                    int u = (axis + 1) % 3; // u + v are orthogonal to axis
                    int v = (axis + 2) % 3;
                    int32_t x[3]; // Sentinel for terminating loop
                    int32_t q[3]; // Points along the direction of axis variable
                    int32_t runs[2 * (dimensions[u] + 1)];
                    int32_t frontier[dimensions[u]]; // Frontier is a list of pointers to polygons
                    int32_t nextFrontier[dimensions[u]];
                    int32_t leftIndex[2 * dimensions[v]];
                    int32_t rightIndex[2 * dimensions[v]];
                    int32_t stack[24 * dimensions[v]];
                    int32_t delta[2][2] = {{0,0}, {0,0}};

                    q[axis] = 1; // TODO:

                    // Initialise sentinel
                    /*
                     * In computer programming, a sentinel value
                     * is a special value in the context of an algorithm which uses its
                     * presence as a condition of termination, typically in a loop or
                     * recursive algorithm.
                     */
                    for (x[axis] = -1; x[axis] < dimensions[axis];) {
                        // Perform monotone polygon subdivision
                        int n = 0;
                        std::vector<monotonePolygon> polygons;
                        int nf = 0;

                        for (x[v] = 0; x[v] < dimensions[v]; ++x[v]) {
                            // Make one pass over the u-scan line of the volume to run-length encode polygon
                            int nr = 0;
                            int p = 0;
                            int c = 0;

                            for (x[u] = 0; x[u] < dimensions[u]; ++x[u], p = c) {
                                // Compute the type for this face
                                int a = (0 <= x[axis] ? f(x[0], x[1], x[2]) : 0);
                                int b = (x[axis] < dimensions[axis] - 1 ? f(x[0] + q[0], x[1] + q[1], x[2] + q[2]) : 0);

                                c = a;

                                if ((!a) == (!b)) {
                                    c = 0;
                                } else if(!a) {
                                    c = -b;
                                }

                                // If cell type doesn't match start a new run
                                if (p != c) {
                                    runs[nr++] = x[u];
                                    runs[nr++] = c;
                                }
                            }

                            // Add sentinel run
                            runs[nr++] = dimensions[u];
                            runs[nr++] = 0;

                            // Update frontier by merging runs
                            int fp = 0;
                            for (int i = 0, j = 0; i < nf && j < nr - 2;) {
                                monotonePolygon polygon = polygons[frontier[i]];
                                int polygonLeft = polygon.left[sizeof(polygon.left) - 1][0];
                                int polygonLeft = polygon.right[sizeof(polygon.right) - 1][0];
                                int polygonColor = polygon.color;
                                int runLeft = runs[j]; // Start of run
                                int runRight = runs[j + 2]; // End of run
                                int runColor = runs[j + 1]; // Color of run

                                // Check if we can merge run with polygon
                            }
                        }
                    }
                }
            }
        }
    }
}
