#include "MonotoneMesher.h"

namespace Cubicuous {
    namespace Core {
        namespace Mesher {
            float MonotoneMesher::_getDimensionFromAxis(int axis, float width, float length, float height) {
                return axis == 0 ? width : ( //TODO: Find some way to remove the need for this terrible function
                    axis == 1 ? height : length
                );
            }

            std::vector<MeshPart*> MonotoneMesher::generateMesh(Structure::Structure *structure, float width,
                                                               float length,
                                                               float height) {
                std::vector<glm::vec3> verticies;
                std::vector<std::array<int, 4>> faces;

                // We need to go over the axis x,y and z
                for (int axis = 0; axis < 3; ++axis) {
                    //TODO: Rename all variables to their actual meaning
                    // Orthogonal: https://2.bp.blogspot.com/_CKHEK3fLVDo/TJQw_X0G8lI/AAAAAAAABjw/Tju9XJifRcM/s1600/2-pt-perspective_orthogonal_lines.jpg
                    int u = (axis + 1) % 3; // u + v are orthogonal to axis
                    int v = (axis + 2) % 3;
                    std::vector<int32_t> x(3); // Sentinel for terminating loop
                    std::vector<int32_t> q(3); // Points along the direction of axis variable
                    std::vector<int32_t> runs(2 * this->_getDimensionFromAxis(u + 1, width, length, height));
                    std::vector<int32_t> frontier(this->_getDimensionFromAxis(u, width, length, height)); // Frontier is a list of pointers to polygons
                    std::vector<int32_t> nextFrontier(this->_getDimensionFromAxis(u, width, length, height));
                    std::vector<int32_t> leftIndex(2 * this->_getDimensionFromAxis(v, width, length, height));
                    std::vector<int32_t> rightIndex(2 * this->_getDimensionFromAxis(v, width, length, height));
                    std::vector<int32_t> stack(24 * this->_getDimensionFromAxis(v, width, length, height));
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

                                int a = (0 <= x[axis] ? structure->getVoxel(x[0], x[1], x[2])->getType() : 0);
                                int b = (x[axis] < this->_getDimensionFromAxis(axis, width, length, height) - 1
                                    ? structure->getVoxel(x[0] + q[0], x[1] + q[1], x[2] + q[2])->getType()
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
                            int fp = 0, i, j;
                            for (i = 0, j = 0; i < nf && j < nr - 2;) {
                                MonotonePolygon polygon = polygons[frontier[i]];
                                int polygonLeft = polygon.left[polygon.left.size() - 1][0];
                                int polygonRight = polygon.right[polygon.right.size() - 1][0];
                                int runLeft = runs[j]; // Start of run
                                int runRight = runs[j + 2]; // End of run
                                int runColor = runs[j + 1]; // Color of run

                                // Check if we can merge run with polygon
                                if (runRight > polygonLeft && polygonRight > runLeft && runColor == polygon.type) {
                                    // Merge run
                                    polygon.mergeRun(x[v], runLeft, runRight);

                                    // Insert polygon into frontier
                                    nextFrontier[fp++] = frontier[i];
                                    i++;
                                    j += 2;
                                } else {
                                    // Check if we need to advance the run pointer
                                    if (runRight <= polygonRight) {
                                        if (runColor != 0) {
                                            MonotonePolygon newPolygon = MonotonePolygon(runColor,
                                                                                         x[v],
                                                                                         runLeft,
                                                                                         runRight);

                                            nextFrontier[fp++] = static_cast<int>(polygons.size());
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
                            for (i; i < nf; ++i) {
                                polygons[frontier[i]].closeOff(x[v]);
                            }

                            // Add any extra runs to frontier
                            for(j; j < nr - 2; j += 2) {
                                int rl = runs[j];
                                int rr = runs[j + 2];
                                int rc = runs[j + 1];

                                if (rc != 0) {
                                    MonotonePolygon newPolygon = MonotonePolygon(rc, x[v], rl, rr);
                                    nextFrontier[fp++] = polygons.size();
                                    polygons.push_back(newPolygon);
                                }
                            }

                            // Copy tmp to frontier
                            frontier = nextFrontier;
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
                            bool flipped = false;

                            for (int j = 0; j < polygon.left.size(); ++j) {
                                leftIndex[j] = static_cast<int>(verticies.size());
                                float y[3] = {0.0f, 0.0f, 0.0f};
                                int z[2] = {polygon.left[j][0], polygon.left[j][1]};
                                y[axis] = x[axis];
                                y[u] = z[0];
                                y[v] = z[1];
                                verticies.push_back(glm::vec3(y[0], y[1], y[2]));
                            }

                            for (int j = 0; j < polygon.right.size(); ++j) {
                                rightIndex[j] = static_cast<int>(verticies.size());
                                float y[3] = {0.0f, 0.0f, 0.0f};
                                int z[2] = {polygon.right[j][0], polygon.right[j][1]};
                                y[axis] = x[axis];
                                y[u] = z[0];
                                y[v] = z[1];
                                verticies.push_back(glm::vec3(y[0], y[1], y[2]));
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
                                            faces.push_back({ stack[bottom], stack[bottom + 3], idx, polygon.type});
                                        } else {
                                            faces.push_back({ stack[bottom + 3], stack[bottom], idx, polygon.type});
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
                                                faces.push_back({stack[top - 3], stack[top - 6], idx, polygon.type});
                                            } else {
                                                faces.push_back({stack[top - 6], stack[top - 3], idx, polygon.type});
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

                std::vector<MeshPart*> meshParts;
                for(int faceIndex = 0; faceIndex < faces.size(); faceIndex++) {
                    meshParts.push_back(new MeshPart(faces[faceIndex][3], new glm::vec3[3] {
                            verticies[faces[faceIndex][0]], verticies[faces[faceIndex][1]], verticies[faces[faceIndex][2]]
                    }));
                }

                return meshParts;
            }
        }
    }
}
