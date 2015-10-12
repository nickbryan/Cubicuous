#include "MonotoneMesher.h"
#include "../../Debugging/Logger.h"

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
                std::vector<glm::vec3> vertices;
                std::vector<std::array<int, 4>> faces;
                std::vector<Graphics::Renderer::IRenderer*> faceRenderers;

                // We need to go over the axis x,y and z
                for (int axis = 0; axis < 3; ++axis) {
                    //TODO: Rename all variables to their actual meaning
                    int u = (axis + 1) % 3; // u + v are orthogonal to axis
                    int v = (axis + 2) % 3;
                    std::vector<int32_t> pos(3); // Sentinel for terminating loop
                    std::vector<int32_t> q(3); // Points along the direction of axis variable
                    std::vector<int32_t> runs(2 * (1 + this->_getDimensionFromAxis(u, width, length, height)));
                    std::vector<int32_t> frontier(this->_getDimensionFromAxis(u, width, length, height)); // Frontier is a list of pointers to polygons
                    std::vector<int32_t> nextFrontier(this->_getDimensionFromAxis(u, width, length, height));
                    std::vector<int32_t> leftIndex(2 * this->_getDimensionFromAxis(v, width, length, height));
                    std::vector<int32_t> rightIndex(2 * this->_getDimensionFromAxis(v, width, length, height));
                    std::vector<int32_t> stack(24 * this->_getDimensionFromAxis(v, width, length, height));
                    std::vector<Graphics::Renderer::IRenderer*> runRenderers;
                    int32_t delta[2][2] = {{0,0}, {0,0}};

                    q[axis] = 1;

                    for (pos[axis] = -1; pos[axis] < this->_getDimensionFromAxis(axis, width, length, height); ) {
                        // Perform monotone polygon subdivision
                        std::vector<MonotonePolygon> polygons;
                        int nf = 0;

                        for (pos[v] = 0; pos[v] < this->_getDimensionFromAxis(v, width, length, height); ++pos[v]) {
                            // Make one pass over the u-scan line of the volume to run-length encode polygon
                            int nr = 0;
                            Graphics::Renderer::IRenderer* currentRunRenderer = nullptr;

                            for (pos[u] = 0; pos[u] < this->_getDimensionFromAxis(u, width, length, height); ++pos[u]) {
                                // Each face has a type, only adjacent voxels of the same type can be merged.
                                // In the Javascript implementation, the value of each voxel in the volume is a binary
                                // version of the hexadecimal hash code that will make up the colour

                                Structure::Voxel* aVoxel = (0 <= pos[axis] ? structure->getVoxel(pos[0], pos[1], pos[2]) : nullptr);
                                Structure::Voxel* bVoxel = (pos[axis] < this->_getDimensionFromAxis(axis, width, length, height) - 1
                                                            ? structure->getVoxel(pos[0] + q[0], pos[1] + q[1], pos[2] + q[2])
                                                            : nullptr);

                                Graphics::Renderer::IRenderer* nextRenderer = nullptr;
                                if (aVoxel != nullptr && bVoxel != nullptr && aVoxel->getRenderer()->isSameAs(bVoxel->getRenderer())) {
                                    //The voxel is of the same type, no need to start a new run
                                    nextRenderer = nullptr;
                                }
                                else if(aVoxel == nullptr) {
                                    //Start a new run, we have a new type of voxel
                                    nextRenderer = bVoxel->getRenderer();
                                }
                                else {
                                    //Start a new run, we have a new type of voxel
                                    nextRenderer = aVoxel->getRenderer();
                                }

                                // If cell type doesn't match start a new run
                                if ((currentRunRenderer == nextRenderer && nextRenderer == nullptr) || currentRunRenderer == nullptr || currentRunRenderer->isSameAs(nextRenderer)) {
                                    runs.push_back(pos[u]);
                                    nr++;
                                    runs.push_back(0); //TODO: Remove this from array and adjust all accessing of runs array to access at new index
                                    nr++;
                                    runRenderers.push_back(nextRenderer);

                                    if(axis == 0) {
                                        Debugging::Logger::log((currentRunRenderer == nullptr ? "from none to one"
                                                                                              : "from one to one"));
                                    }
                                }

                                currentRunRenderer = nextRenderer;
                            }

                            // Add sentinel run
                            runs.push_back(this->_getDimensionFromAxis(u, width, length, height));
                            nr++;
                            runs.push_back(0);
                            nr++;

                            // Update frontier by merging runs
                            int fp = 0, i, j;
                            for (i = 0, j = 0; i < nf && j < nr - 2;) {
                                MonotonePolygon polygon = polygons[frontier[i]];
                                int polygonLeft = polygon.left[polygon.left.size() - 1][0];
                                int polygonRight = polygon.right[polygon.right.size() - 1][0];
                                int runLeft = runs[j]; // Start of run
                                int runRight = runs[j + 2]; // End of run
//                                int runColor = runs[j + 1]; // Color of run
                                Graphics::Renderer::IRenderer* runRenderer = runRenderers[j];

                                // Check if we can merge run with polygon
                                if (runRight > polygonLeft && polygonRight > runLeft && polygon.renderer != nullptr && polygon.renderer->isSameAs(runRenderer)) {
                                    // Merge run
                                    polygon.mergeRun(pos[v], runLeft, runRight);

                                    // Insert polygon into frontier
                                    nextFrontier.push_back(frontier[i]);
                                    fp++;
                                    i++;
                                    j += 2;
                                } else {
                                    // Check if we need to advance the run pointer
                                    if (runRight <= polygonRight) {
                                        if (runRenderer != nullptr) {
                                            MonotonePolygon newPolygon = MonotonePolygon(runRenderer, pos[v], runLeft, runRight);
                                            nextFrontier.push_back(static_cast<int>(polygons.size()));
                                            fp++;
                                            polygons.push_back(newPolygon);
                                        }
                                        j += 2;
                                    }
                                    // Check if we  need to advance the frontier pointer
                                    if (polygonRight <= runRight) {
                                        polygon.closeOff(pos[v]);
                                        i++;
                                    }
                                }
                            }

                            // Close off any residual polygons
                            for (i; i < nf; ++i) {
                                polygons[frontier[i]].closeOff(pos[v]);
                            }

                            // Add any extra runs to frontier
                            for(j; j < nr - 2; j += 2) {
                                if (runRenderers[j] != nullptr) {
                                    MonotonePolygon newPolygon = MonotonePolygon(runRenderers[j], pos[v], runs[j], runs[j + 2]);
                                    nextFrontier.push_back(polygons.size());
                                    fp++;
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

                        pos[axis]++;

                        // Now we need to triangulate each monotone polygon
                        for (int i = 0; i < polygons.size(); ++i) {
                            MonotonePolygon polygon = polygons[i];
                            bool flipped = false;

                            for (int j = 0; j < polygon.left.size(); ++j) {
                                leftIndex[j] = static_cast<int>(vertices.size());
                                float y[3] = {0.0f, 0.0f, 0.0f};
                                int z[2] = {polygon.left[j][0], polygon.left[j][1]};
                                y[axis] = pos[axis];
                                y[u] = z[0];
                                y[v] = z[1];
                                vertices.push_back(glm::vec3(y[0], y[1], y[2]));
                            }

                            for (int j = 0; j < polygon.right.size(); ++j) {
                                rightIndex[j] = static_cast<int>(vertices.size());
                                float y[3] = {0.0f, 0.0f, 0.0f};
                                int z[2] = {polygon.right[j][0], polygon.right[j][1]};
                                y[axis] = pos[axis];
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

                            stack.push_back(leftIndex[0]);
                            top++;
                            stack.push_back(polygon.left[0][0]);
                            top++;
                            stack.push_back(polygon.left[0][1]);
                            top++;

                            stack.push_back(rightIndex[0]);
                            top++;
                            stack.push_back(polygon.right[0][0]);
                            top++;
                            stack.push_back(polygon.right[0][1]);
                            top++;

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
                                            faces.push_back({ stack[bottom], stack[bottom + 3], idx });
                                        } else {
                                            faces.push_back({ stack[bottom + 3], stack[bottom], idx });
                                        }

                                        faceRenderers[faces.size() - 1] = polygon.renderer;
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
                                                faces.push_back({stack[top - 3], stack[top - 6], idx });
                                            } else {
                                                faces.push_back({stack[top - 6], stack[top - 3], idx });
                                            }

                                            faceRenderers[faces.size() - 1] = polygon.renderer;
                                        }
                                        top -= 3;
                                    }
                                }

                                // Push Vertex
                                stack.push_back(idx);
                                top++;
                                stack.push_back(vert[0]);
                                top++;
                                stack.push_back(vert[1]);
                                top++;

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
                    meshParts.push_back(new MeshPart(faceRenderers[faceIndex], std::vector<glm::vec3>({
                            vertices[faces[faceIndex][0]], vertices[faces[faceIndex][1]], vertices[faces[faceIndex][2]]
                    })));
                }

                return meshParts;
            }
        }
    }
}
