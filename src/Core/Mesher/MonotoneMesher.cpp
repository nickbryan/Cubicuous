#include "MonotoneMesher.h"

namespace Cubicuous {
    namespace Core {
        namespace Mesher {
            Structure::Voxel* MonotoneMesher::_getVoxelFromPosition(Structure::Structure* structure, int width, int length, int height,
                                                  int x, int y, int z) {
              //TODO: Figure out the commented out code to make sure it has been correctly translated
//                return volume[i + dims[0] * (j + dims[1] * k)];
                return structure->getVoxel(x * width, y + height, z);
            }

            int MonotoneMesher::_getDimensionFromAxis(int axis, int width, int length, int height) {
                return axis == 0 ? width : ( //TODO: Find some way to remove the need for this terrible function
                    axis == 1 ? height : length
                );
            }

            std::array<MeshPart> MonotoneMesher::generateMesh(Structure::Structure* structure, int width, int length, int height) {
                std::vector<glm::vec3> vertices;
                std::vector<int[4]> faces;

                // We need to go over the axis x,y and z
                for (int axis = 0; axis < 3; ++axis) {
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
                                // Each face has a type, only adjacent voxels of the same type can be merged.
                                // In the Javascript implementation, the value of each voxel in the volume is a binary
                                // version of the hexdecimal hash code that will make up the colour

                                int a = (0 <= x[axis] ? this->_getVoxelFromPosition(structure, width, length, height, x[0], x[1], x[2])->getType() : 0);
                                int b = (x[axis] < this->_getDimensionFromAxis(axis, width, length, height) - 1
                                    ? this->_getVoxelFromPosition(structure, width, length, height, x[0] + q[0], x[1] + q[1], x[2] + q[2])->getType()
                                    : 0);

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
                                int polygonLeft = polygon.left[polygon.left.size() - 1][0];
                                int polygonRight = polygon.right[polygon.right.size() - 1][0];
                                int polygonColor = polygon.color;
                                int runLeft = runs[j]; // Start of run
                                int runRight = runs[j + 2]; // End of run
                                int runColor = runs[j + 1]; // Color of run

                                // Check if we can merge run with polygon
                                if (runRight > polygonLeft && polygonRight > runLeft && runColor == polygonColor) {
                                    // Merge run
                                    polygon.mergeRun(x[v], runLeft, runRight);

                                    // Insert polygon into frontier
                                    nextFrontier[fp++] = frontier[i];
                                    i++;
                                    j += 2;
                                } else {
                                    // Check if we need to advance the run pointer
                                    if (runRight <= polygonRight) {
                                        if (!!runColor) {
                                            MonotonePolygon newPolygon = MonotonePolygon(runColor,
                                                                                         x[v],
                                                                                         runLeft,
                                                                                         runRight);

                                            nextFrontier[fp++] = polygons.size();
                                            polygons.push_back(newPolygon);
                                        }
                                        j += 2;
                                    }
                                    // Check if we  need to advance the frontier pointer
                                    if (polygonRight <= runRight) {
                                        polygon.closeOff(x[v]);
                                        i++;
                                    }
                                }
                            }
                            // Close off any residual polygons
                            for (; i < nf; ++i) {
                                polygons[frontier[i]].closeOff(x[v]);
                            }

                            // Add any extra runs to frontier
                            for(; j < nr - 2; j += 2) {
                                int rl = runs[j];
                                int rr = runs[j + 2];
                                int rc = runs[j + 1];

                                if (!!rc) {
                                    MonotonePolygon newPolygon = MonotonePolygon(rc, x[v], rl, rr);
                                    nextFrontier[fp++] = polygons.size();
                                    polygons.push_back(newPolygon);
                                }
                            }
                            // Swap frontiers
                            int32_t tmp[sizeof(nextFrontier) / sizeof(*nextFrontier)];

                            // Copy nextFrontier to tmp
                            std::copy(std::begin(nextFrontier), std::end(nextFrontier), std::begin(tmp));

                            // Copy frontier to nextFrontier
                            // TODO: check if this will overwrite the array
                            std::copy(std::begin(frontier), std::end(frontier), std::begin(nextFrontier));

                            // Copy tmp to frontier
                            std::copy(std::begin(tmp), std::end(tmp), std::begin(frontier));

                            nf = fp;
                        }
                        // Close off frontier
                        for (int i = 0; i < nf; ++i) {
                            MonotonePolygon polygon = polygons[frontier[i]];
                            polygon.closeOff(this->_getDimensionFromAxis(v, width, length, height));
                        }
                        // --- Monotone subdivision of polygon is complete at this point ---

                        x[axis]++;

                        // Now we need to triangulate each monotone polygon
                        for (int i = 0; i < polygons.size(); ++i) {
                            MonotonePolygon polygon = polygons[i];
                            int color = polygon.color;
                            bool flipped = false;

                            if (color < 0) {
                                flipped = true;
                                color = -color;
                            }

                            for (int j = 0; j < polygon.left.size(); ++j) {
                                leftIndex[j] = vertices.size();
                                float y[3] = {0.0f, 0.0f, 0.0f};
                                int z[2] = {polygon.left[j][0], polygon.left[j][1]}
                                y[axis] = x[axis];
                                y[u] = z[0];
                                y[v] = z[1];
                                vertices.push_back(glm::vec3(y[0], y[1], y[2]));
                            }

                            for (int j = 0; j < polygon.right.size(); ++j) {
                                rightIndex[j] = vertices.size();
                                float y[3] = {0.0f, 0.0f, 0.0f};
                                int z[2] = {polygon.right[j][0], polygon.right[j][1]};
                                y[axis] = x[axis];
                                y[u] = z[0];
                                y[v] = z[1];
                                vertices.push_back(glm::vec3(y[0], y[1], y[2]));
                            }

                            // Triangulate the monotone polygon
                            int bottom = 0;
                            int top = 0;
                            int li = 1;
                            int ri = 1;
                            bool side = true; // true = right, false = left

                            stack[top++] = leftIndex[0];
                            stack[top++] = polygon.left[0][0];
                            stack[top++] = polygon.left[0][1];

                            stack[top++] = rightIndex[0];
                            stack[top++] = polygon.right[0][0];
                            stack[top++] = polygon.right[0][1];

                            while (li < polygon.left.size() || ri < polygon.right.size()) {
                                // Compute next size
                                bool nSide = false;

                                if (li == polygon.left.size()) {
                                    nSide = true;
                                } else if (ri != polygon.left.size()) {
                                    int l[2] = {polygon.left[li][0], polygon.left[li][1]};
                                    int r[2] = {polygon.right[ri][0], polygon.right[ri][1]};
                                    nSide = l[1] > r[1];
                                }

                                int idx = nSide ? rightIndex[ri] : leftIndex[li];
                                int vert[2];
                                if (nSide) {
                                    vert[0] = polygon.right[ri][0];
                                    vert[1] = polygon.right[ri][1];
                                } else {
                                    vert[0] = polygon.left[li][0];
                                    vert[1] = polygon.left[li][1];
                                }

                                if (nSide != side) {
                                    // Opposite side
                                    while(bottom + 3 < top) {
                                        if(flipped == nSide) {
                                            faces.push_back({ stack[bottom], stack[bottom + 3], idx, color});
                                        } else {
                                            faces.push_back({ stack[bottom + 3], stack[bottom], idx, color});
                                        }
                                        bottom += 3;
                                    }
                                } else {
                                    // Same side
                                    while (bottom + 3 < top) {
                                        // Compute convexity
                                        for (int j = 0; j < 2; ++j) {
                                            for (int k = 0; k < 2; ++k) {
                                                delta[j][k] = stack[top - 3 * (j + 1) + k + 1] - vert[k];
                                            }
                                        }

                                        int det = delta[0][0] * delta[1][1] - delta[1][0] * delta[0][1];
                                        if (nSide == (det > 0)) {
                                            break;
                                        }

                                        if (det != 0) {
                                            if (flipped == nSide) {
                                                faces.push_back({stack[top - 3], stack[top - 6], idx, color});
                                            } else {
                                                faces.push_back({stack[top - 6], stack[top - 3], idx, color});
                                            }
                                        }
                                        top -= 3;
                                    }
                                }

                                // Push Vertex
                                stack[top++] = idx;
                                stack[top++] = vert[0];
                                stack[top++] = vert[1];

                                //Update loop index
                                if(nSide) {
                                    ++ri;
                                } else {
                                    ++li;
                                }
                                side = nSide;
                            }
                        }
                    }
                }
                return {vertices, faces};
            }
        }
    }
}
