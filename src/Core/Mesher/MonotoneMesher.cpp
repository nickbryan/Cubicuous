#include "MonotoneMesher.h"

namespace Cubicuous {
    namespace Core {
        namespace Mesher {
            Structure::Voxel* MonotoneMesher::_getVoxelFromPosition(Structure::Structure* structure, int width, int length, int height,
                                                  float x, float y, float z) {
              //TODO: Figure out the commented out code to make sure it has been correctly translated
//                return volume[i + dims[0] * (j + dims[1] * k)];
                return structure->getVoxel(x * width, y + height, z);
            }

            int MonotoneMesher::_getDimensionFromAxis(int axis, int width, int length, int height) {
                return axis == 0 ? width : ( //TODO: Find some way to remove the need for this terrible function
                    axis == 1 ? height : length
                );
            }

            void MonotoneMesher::generateMesh(Structure::Structure* structure, int width, int length, int height) {
                // We need to go over the axis x,y and z
                for (int axis = 0; axis < 3; ++axis) {
                    int structureXPosition, struxtureYPosition, structureZPosition;

                    //TODO: Rename all variables to their actual meaning
                    // Orthogonal: https://2.bp.blogspot.com/_CKHEK3fLVDo/TJQw_X0G8lI/AAAAAAAABjw/Tju9XJifRcM/s1600/2-pt-perspective_orthogonal_lines.jpg
                    int u = (axis + 1) % 3; // u + v are orthogonal to axis
                    int v = (axis + 2) % 3;
                    int32_t x[3]; // Sentinel for terminating loop
                    int32_t q[3]; // Points along the direction of axis variable
                    int32_t runs[2 * (this->_getDimensionFromAxis(u + 1, width, length, height))];
                    int32_t frontier[this->_getDimensionFromAxis(u, width, length, height)]; // Frontier is a list of pointers to polygons
                    int32_t nextFrontier[this->_getDimensionFromAxis(u, width, length, height)];
                    int32_t leftIndex[2 * this->_getDimensionFromAxis(v, width, length, height)];
                    int32_t rightIndex[2 * this->_getDimensionFromAxis(v, width, length, height)];
                    int32_t stack[24 * this->_getDimensionFromAxis(v, width, length, height)];
                    int32_t delta[2][2] = {{0,0}, {0,0}};

                    q[axis] = 1;

                    // Initialise sentinel
                    /*
                     * In computer programming, a sentinel value
                     * is a special value in the context of an algorithm which uses its
                     * presence as a condition of termination, typically in a loop or
                     * recursive algorithm.
                     */
                    for (x[axis] = -1; x[axis] < this->_getDimensionFromAxis(axis, width, length, height);) {
                        // Perform monotone polygon subdivision
                        int n = 0;
                        std::vector<MonotonePolygon> polygons;
                        int nf = 0;

                        for (x[v] = 0; x[v] < this->_getDimensionFromAxis(v, width, length, height); ++x[v]) {
                            // Make one pass over the u-scan line of the volume to run-length encode polygon
                            int nr = 0;
                            int p = 0;
                            int c = 0;

                            for (x[u] = 0; x[u] < this->_getDimensionFromAxis(u, width, length, height); ++x[u], p = c) {
                                // Compute the type for this face
                                //TODO: Figure out the value of each voxel in the 3D array and fix this accordingly
                                int a = (0 <= x[axis] ? this->_getVoxelFromPosition(x[0], x[1], x[2]) : 0);
                                int b = (x[axis] < this->_getDimensionFromAxis(axis, width, length, height) - 1 ? this->_getVoxelFromPosition(x[0] + q[0], x[1] + q[1], x[2] + q[2]) : 0);

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
                            runs[nr++] = this->_getDimensionFromAxis(u, width, length, height);
                            runs[nr++] = 0;

                            // Update frontier by merging runs
                            int fp = 0;
                            for (int i = 0, j = 0; i < nf && j < nr - 2;) {
                                MonotonePolygon polygon = polygons[frontier[i]];
                                int polygonLeft = polygon.left[sizeof(polygon.left) - 1][0];
                                int polygonRight = polygon.right[sizeof(polygon.right) - 1][0];
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
