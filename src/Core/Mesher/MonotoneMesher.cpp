#include "MonotoneMesher.h"
#include "../../Debugging/Logger.h"

namespace Cubicuous {
    namespace Core {
        namespace Mesher {
            float MonotoneMesher::_getDimensionFromAxis(int axis, float width, float length, float height) {
                return axis == 0 ? width : ( //TODO: Find some way to remove the need for this terrible function
                        axis == 1 ? height : length);
            }

            std::vector<MeshPart*> MonotoneMesher::generateMesh(Structure::Structure* structure, float width,
                                                                float length, float height) {
                std::vector<glm::vec3> vertices;
                std::vector<std::array<int, 4>> faces;
                std::vector<Graphics::Renderer::IRenderer*> faceRenderers;

                // We need to go over the axis x,y and z
                for (int axis = 0; axis < 3; ++axis) {
                    Debugging::Logger::log("Processing axis " + Debugging::Logger::toLoggable(axis));

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
                    int32_t delta[2][2] = {{0, 0}, {0, 0}};

                    q[axis] = 1;

                    Debugging::Logger::log("Doing pos loop, pos[axis] = " + Debugging::Logger::toLoggable(pos[axis]) +", Axis Dimensions = " + Debugging::Logger::toLoggable(this->_getDimensionFromAxis(axis, width, length, height)));
                    for (pos[axis] = -1; pos[axis] < this->_getDimensionFromAxis(axis, width, length, height);) {
                        // Perform monotone polygon subdivision
                        std::vector<MonotonePolygon> polygons;
                        int nf = 0;
                        Debugging::Logger::log("    Pos[axis] loop = " + Debugging::Logger::toLoggable(pos[axis]) + ", nf = " + Debugging::Logger::toLoggable(nf));
                        Debugging::Logger::log("    Start pos[v] loop, pos[v] = " + Debugging::Logger::toLoggable(pos[v]) + ", v dimensions = " + Debugging::Logger::toLoggable(this->_getDimensionFromAxis(v, width, length, height)));

                        for (pos[v] = 0; pos[v] < this->_getDimensionFromAxis(v, width, length, height); ++pos[v]) {
                            // Make one pass over the u-scan line of the volume to run-length encode polygon
                            int nr = 0;
                            Graphics::Renderer::IRenderer* currentRunRenderer = nullptr;

                            Debugging::Logger::log("        Pos[v] loop at " + Debugging::Logger::toLoggable(pos[v]) + ", nr = " + Debugging::Logger::toLoggable(nr));
                            Debugging::Logger::log("        Start Pos[u] loop, pos[u] = " + Debugging::Logger::toLoggable(pos[u]) +", u dimensions = " + Debugging::Logger::toLoggable(this->_getDimensionFromAxis(u, width, length, height)));

                            for (pos[u] = 0; pos[u] < this->_getDimensionFromAxis(u, width, length, height); ++pos[u]) {
                                Debugging::Logger::log("            Pos[u] loop at " + Debugging::Logger::toLoggable(pos[u]));
                                // Each face has a type, only adjacent voxels of the same type can be merged.
                                // In the Javascript implementation, the value of each voxel in the volume is a binary
                                // version of the hexadecimal hash code that will make up the colour

                                Structure::Voxel* aVoxel = (0 <= pos[axis] ? structure->getVoxel(pos[0], pos[1], pos[2])
                                                                           : nullptr);
                                Structure::Voxel* bVoxel = (pos[axis] <
                                                            this->_getDimensionFromAxis(axis, width, length, height) - 1
                                                            ? structure->getVoxel(pos[0] + q[0], pos[1] + q[1],
                                                                                  pos[2] + q[2]) : nullptr);

                                Debugging::Logger::log("            A voxel " + std::string(aVoxel == nullptr ? "not found" : "found") + ". B voxel " + std::string(bVoxel == nullptr ? "not found" : "found"));
                                Graphics::Renderer::IRenderer* nextRenderer = nullptr;
                                if (aVoxel != nullptr && bVoxel != nullptr &&
                                    aVoxel->getRenderer()->isSameAs(bVoxel->getRenderer())) {
                                    //The voxel is of the same type, no need to start a new run
                                    nextRenderer = nullptr;
                                    Debugging::Logger::log("            Set nextRenderer to null, a and b are the same");
                                }
                                else if (aVoxel == nullptr) {
                                    //Start a new run, we have a new type of voxel
                                    nextRenderer = bVoxel->getRenderer();
                                    Debugging::Logger::log("            Set nextRenderer to b renderer, a voxel not found");
                                }
                                else {
                                    //Start a new run, we have a new type of voxel
                                    nextRenderer = aVoxel->getRenderer();
                                    Debugging::Logger::log("            Set nextRenderer to a renderer, a and b different");
                                }

                                // If cell type doesn't match start a new run
                                if (nextRenderer != nullptr && !nextRenderer->isSameAs(currentRunRenderer)) {
                                    runs.push_back(pos[u]);
                                    nr++;
                                    runs.push_back(0);
                                    //TODO: Remove this from array and adjust all accessing of runs array to access at new index
                                    nr++;
                                    runRenderers.push_back(nextRenderer);
                                    Debugging::Logger::log("            starting new run, nr now " + Debugging::Logger::toLoggable(nr));
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

                            Debugging::Logger::log("        Pos[u] loop finished, nr at " + Debugging::Logger::toLoggable(nr) +", total runs " + Debugging::Logger::toLoggable(runs.size()));
                            Debugging::Logger::log("        Start merge run check loop, nf " + Debugging::Logger::toLoggable(nf));
                            for (i = 0, j = 0; i < nf && j < nr - 2;) {
                                Debugging::Logger::log("            Merge run loop at i = " + Debugging::Logger::toLoggable(i) +", j = " + Debugging::Logger::toLoggable(j) + ", fp = " + Debugging::Logger::toLoggable(fp));

                                MonotonePolygon polygon = polygons[frontier[i]];
                                int polygonLeft = polygon.left[polygon.left.size() - 1][0];
                                int polygonRight = polygon.right[polygon.right.size() - 1][0];
                                int runLeft = runs[j]; // Start of run
                                int runRight = runs[j + 2]; // End of run
//                                int runColor = runs[j + 1]; // Color of run
                                Graphics::Renderer::IRenderer* runRenderer = runRenderers[j];
                                Debugging::Logger::log("            Polygon left = " + Debugging::Logger::toLoggable(polygonLeft) +", Polygon right = " + Debugging::Logger::toLoggable(polygonRight) +" run left = " + Debugging::Logger::toLoggable(runLeft) + ", run right = " +Debugging::Logger::toLoggable(runRight));

                                // Check if we can merge run with polygon
                                if (runRight > polygonLeft && polygonRight > runLeft && polygon.renderer != nullptr &&
                                    polygon.renderer->isSameAs(runRenderer)) {
                                    Debugging::Logger::log("            Running merge run on polgyon and adding to next frontier");

                                    // Merge run
                                    polygon.mergeRun(pos[v], runLeft, runRight);

                                    // Insert polygon into frontier
                                    nextFrontier.push_back(frontier[i]);
                                    fp++;
                                    i++;
                                    j += 2;
                                }
                                else {
                                    Debugging::Logger::log("            Can't run merge run");

                                    // Check if we need to advance the run pointer
                                    if (runRight <= polygonRight) {
                                        Debugging::Logger::log("            polygonRight greater than runRight. Attempting to update frontier and polygons. Increased j");
                                        if (runRenderer != nullptr) {
                                            nextFrontier.push_back(static_cast<int>(polygons.size()));
                                            fp++;
                                            polygons.push_back(MonotonePolygon(runRenderer, pos[v], runLeft, runRight));
                                            Debugging::Logger::log("            Updated polygons, fp and frontier");
                                        }
                                        j += 2;
                                    }
                                    // Check if we  need to advance the frontier pointer
                                    if (polygonRight <= runRight) {
                                        Debugging::Logger::log("            PolygonRight less than runRight, closing off polygon");
                                        polygon.closeOff(pos[v]);
                                        i++;
                                    }
                                }
                            }

                            Debugging::Logger::log("        Finished polygon merge run loop, closing remaining polygons. nf = " + Debugging::Logger::toLoggable(nf));
                            // Close off any residual polygons
                            for (i; i < nf; ++i) {
                                Debugging::Logger::log("            Closing remaining polygon " + Debugging::Logger::toLoggable(i) + " using " + Debugging::Logger::toLoggable(pos[v]));
                                polygons[frontier[i]].closeOff(pos[v]);
                            }

                            // Add any extra runs to frontier
                            Debugging::Logger::log("        Closed remaining polygons. Starting extra run loop. J = " + Debugging::Logger::toLoggable(j) + ", nr = " + Debugging::Logger::toLoggable(nr));
                            for (j; j < nr - 2; j += 2) {
                                Debugging::Logger::log("            Extra run loop at " + Debugging::Logger::toLoggable(j));

                                if (runRenderers[j] != nullptr) {
                                    nextFrontier.push_back(polygons.size());
                                    fp++;
                                    polygons.push_back(MonotonePolygon(runRenderers[j], pos[v], runs[j], runs[j + 2]));
                                    Debugging::Logger::log("            Run renderer not null, updating frontier");
                                }
                            }

                            frontier = nextFrontier;
                            nf = fp;
                        }

                        Debugging::Logger::log("    Finished Pos[v] loop, closing off generated frontiers, nf = " + Debugging::Logger::toLoggable(nf));
                        // Close off frontier
                        for (int i = 0; i < nf; ++i) {
                            Debugging::Logger::log("        Closing off frontier polygon " + Debugging::Logger::toLoggable(i));
                            polygons[frontier[i]].closeOff(this->_getDimensionFromAxis(v, width, length, height));
                        }

                        // --- Monotone subdivision of polygon is complete at this point ---
                        pos[axis]++;
                        Debugging::Logger::log("    Montone subdivision of polygons complete, triangulation beginning. Total polygons = " + polygons.size());

                        // Now we need to triangulate each monotone polygon
                        for (int i = 0; i < polygons.size(); ++i) {
                            Debugging::Logger::log("        Triangulation loop at " + Debugging::Logger::toLoggable(i));

                            MonotonePolygon polygon = polygons[i];
                            bool flipped = false;

                            Debugging::Logger::log("        Generating left side veritces ");
                            for (int j = 0; j < polygon.left.size(); ++j) {
                                Debugging::Logger::log("            Generating left side veritces for polygon " + Debugging::Logger::toLoggable(j));
                                leftIndex[j] = static_cast<int>(vertices.size());
                                float y[3] = {0.0f, 0.0f, 0.0f};
                                int z[2] = {polygon.left[j][0], polygon.left[j][1]};
                                y[axis] = pos[axis];
                                y[u] = z[0];
                                y[v] = z[1];
                                vertices.push_back(glm::vec3(y[0], y[1], y[2]));
                                Debugging::Logger::log("            Generated " + Debugging::Logger::toLoggable(y[0]) + ", " + Debugging::Logger::toLoggable(y[1]) + ", " + Debugging::Logger::toLoggable(y[2]));
                            }

                            Debugging::Logger::log("        Generating right side veritces ");
                            for (int j = 0; j < polygon.right.size(); ++j) {
                                Debugging::Logger::log("            Generating right side veritces for polygon " + Debugging::Logger::toLoggable(j));
                                rightIndex[j] = static_cast<int>(vertices.size());
                                float y[3] = {0.0f, 0.0f, 0.0f};
                                int z[2] = {polygon.right[j][0], polygon.right[j][1]};
                                y[axis] = pos[axis];
                                y[u] = z[0];
                                y[v] = z[1];
                                vertices.push_back(glm::vec3(y[0], y[1], y[2]));
                                Debugging::Logger::log("            Generated " + Debugging::Logger::toLoggable(y[0]) + ", " + Debugging::Logger::toLoggable(y[1]) + ", " + Debugging::Logger::toLoggable(y[2]));
                            }

                            Debugging::Logger::log("        Generated all verticies");
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

                            Debugging::Logger::log("        Triangulation begun, top now at " + Debugging::Logger::toLoggable(top) + ", stack size of " + Debugging::Logger::toLoggable(stack.size()));
                            Debugging::Logger::log("        Beginning triangulation, li = " + Debugging::Logger::toLoggable(li) + ", ri = " + Debugging::Logger::toLoggable(ri) + ". Left polygon size ="  + Debugging::Logger::toLoggable(polygon.left.size())  + ". Right polygon size ="  + Debugging::Logger::toLoggable(polygon.right.size()));

                            while (li < polygon.left.size() || ri < polygon.right.size()) {
                                Debugging::Logger::log("            triangulation at, li = " + Debugging::Logger::toLoggable(li) + ", ri = " + Debugging::Logger::toLoggable(ri) + ", top = " + Debugging::Logger::toLoggable(top) + ", bottom = " + Debugging::Logger::toLoggable(bottom) + ". Left polygon size ="  + Debugging::Logger::toLoggable(polygon.left.size())  + ". Right polygon size ="  + Debugging::Logger::toLoggable(polygon.right.size()) + " side = " + std::string(side ? "right" : "left"));
                                // Compute next size
                                bool nSide = false;

                                if (li == polygon.left.size()) {
                                    Debugging::Logger::log("            nSide set to true, li == polygonLeft");
                                    nSide = true;
                                }
                                else if (ri != polygon.left.size()) {
                                    nSide = polygon.left[li][1] > polygon.right[ri][1];
                                    Debugging::Logger::log("            nSide set to " + std::string(nSide ? "true" : "false") + ", ri != polygonLeft. Polygon.left[li][1] = " + Debugging::Logger::toLoggable(polygon.left[li][1]) + " Polygon.left[li][1] = " + Debugging::Logger::toLoggable(polygon.right[ri][1]));
                                }


                                int idx = nSide ? rightIndex[ri] : leftIndex[li];
                                std::array<int, 2> vert = (nSide ? polygon.right[ri] : polygon.left[li]);
                                Debugging::Logger::log("            Calculated nSide. idx set as " + Debugging::Logger::toLoggable(idx) + ", vert[0] " + Debugging::Logger::toLoggable(vert[0]) + ", vert[1] " + Debugging::Logger::toLoggable(vert[1]));

                                if (nSide != side) {
                                    Debugging::Logger::log("            On opposite side, update faces from bottom = " + Debugging::Logger::toLoggable(bottom + 3) + " to top = " + Debugging::Logger::toLoggable(top));
                                    // Opposite side
                                    while (bottom + 3 < top) {
                                        Debugging::Logger::log("                Updating faces for bottom " + Debugging::Logger::toLoggable(bottom));
                                        if (flipped == nSide) {
                                            Debugging::Logger::log("                Flipped face same face as nSide. Push as bottom, bottom + 3 with values from stack as " + Debugging::Logger::toLoggable(stack[bottom]) + ", " +  Debugging::Logger::toLoggable(stack[bottom + 3]));
                                            faces.push_back({stack[bottom], stack[bottom + 3], idx});
                                        }
                                        else {
                                            Debugging::Logger::log("                Flipped face same face as nSide. Push as bottom + 3, bottom with values from stack as " + Debugging::Logger::toLoggable(stack[bottom + 3]) + ", " +  Debugging::Logger::toLoggable(stack[bottom]));
                                            faces.push_back({stack[bottom + 3], stack[bottom], idx});
                                        }

                                        faceRenderers[faces.size() - 1] = polygon.renderer;
                                        bottom += 3;
                                        Debugging::Logger::log("                Updating faceRenderer " + Debugging::Logger::toLoggable(faces.size()));
                                    }
                                }
                                else {
                                    Debugging::Logger::log("            update faces from bottom = " + Debugging::Logger::toLoggable(bottom + 3) + " to top = " + Debugging::Logger::toLoggable(top));
                                    // Same side
                                    while (bottom + 3 < top) {
                                        Debugging::Logger::log("                Start convexity calculation. Updating faces for bottom " + Debugging::Logger::toLoggable(bottom));

                                        // Compute convexity
                                        for (int j = 0; j < 2; ++j) {
                                            Debugging::Logger::log("                    Calculating convexity for " + Debugging::Logger::toLoggable(j));

                                            for (int k = 0; k < 2; ++k) {
                                                delta[j][k] = stack[top - 3 * (j + 1) + k + 1] - vert[k];
                                                Debugging::Logger::log("                        Calculating delta convexity for " + Debugging::Logger::toLoggable(k) + " as " + Debugging::Logger::toLoggable(delta[j][k]));
                                            }
                                        }

                                        int det = delta[0][0] * delta[1][1] - delta[1][0] * delta[0][1];
                                        Debugging::Logger::log("                Calculating det based upon delta, det = " + Debugging::Logger::toLoggable(det));
                                        if (nSide == (det > 0)) {
                                            Debugging::Logger::log("                det side same as nSide, breaking from face update");
                                            break;
                                        }

                                        if (det != 0) {
                                            Debugging::Logger::log("                det not 0, update faces");
                                            if (flipped == nSide) {
                                                Debugging::Logger::log("                Flipped same as nSide, update using top - 3, top - 6, stack values " + Debugging::Logger::toLoggable(stack[top - 3]) + ", " + Debugging::Logger::toLoggable(stack[top - 6]));
                                                faces.push_back({stack[top - 3], stack[top - 6], idx});
                                            }
                                            else {
                                                Debugging::Logger::log("                Flipped same as nSide, update using top - 6, top - 3, stack values " + Debugging::Logger::toLoggable(stack[top - 6]) + ", " + Debugging::Logger::toLoggable(stack[top - 3]));
                                                faces.push_back({stack[top - 6], stack[top - 3], idx});
                                            }

                                            faceRenderers[faces.size() - 1] = polygon.renderer;
                                            Debugging::Logger::log("                Setting faceRenderer " + Debugging::Logger::toLoggable(faces.size() - 1));
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
                                Debugging::Logger::log("            Completed update of faces and face renders. Pushing vertex to stack. Stack size now " + Debugging::Logger::toLoggable(stack.size()) + ", top = " + Debugging::Logger::toLoggable(top));

                                //Update loop index
                                if (nSide) {
                                    Debugging::Logger::log("            Increased ri side var");
                                    ++ri;
                                }
                                else {
                                    Debugging::Logger::log("            Increased li side var");
                                    ++li;
                                }

                                side = nSide;
                                Debugging::Logger::log("            Set last side var to " + std::string(side ? "right" : "left"));
                            }

                            Debugging::Logger::log("        Finished triangulation of polygon. Total stack size " + Debugging::Logger::toLoggable(stack.size()) + ", total top = " + Debugging::Logger::toLoggable(top) + ", total bottom = " + Debugging::Logger::toLoggable(bottom) + " final li " + Debugging::Logger::toLoggable(li) + ", final ri = " + Debugging::Logger::toLoggable(ri));
                        }

                        Debugging::Logger::log("    Finished all polygon triangulation");
                    }

                    Debugging::Logger::log("Finished polygon generation for axis");
                }

                Debugging::Logger::log("Finished polygon generation, converting polgyon faces to mesh parts for rendering. Total faces = " + Debugging::Logger::toLoggable(faces.size()) + ", Total vertices = " + Debugging::Logger::toLoggable(vertices.size()));

                std::vector<MeshPart*> meshParts;
                for (int faceIndex = 0; faceIndex < faces.size(); faceIndex++) {
                    Debugging::Logger::log("    Converting face " + Debugging::Logger::toLoggable(faceIndex));

                    meshParts.push_back(new MeshPart(faceRenderers[faceIndex], std::vector<glm::vec3>({
                        vertices[faces[faceIndex][0]], vertices[faces[faceIndex][1]],vertices[faces[faceIndex][2]]
                    })));

                    Debugging::Logger::log("    Converted as (" + Debugging::Logger::toLoggable(vertices[faces[faceIndex][0]].x) + ", " + Debugging::Logger::toLoggable(vertices[faces[faceIndex][0]].y) + ", " + Debugging::Logger::toLoggable(vertices[faces[faceIndex][0]].z) + "), " +
                                          "(" + Debugging::Logger::toLoggable(vertices[faces[faceIndex][1]].x) + ", " + Debugging::Logger::toLoggable(vertices[faces[faceIndex][1]].y) + ", " + Debugging::Logger::toLoggable(vertices[faces[faceIndex][1]].z) + "), "
                                          "(" + Debugging::Logger::toLoggable(vertices[faces[faceIndex][2]].x) + ", " + Debugging::Logger::toLoggable(vertices[faces[faceIndex][2]].y) + ", " + Debugging::Logger::toLoggable(vertices[faces[faceIndex][2]].z) + "), ");
                }

                Debugging::Logger::log("MontoneMesher complete, generated " + Debugging::Logger::toLoggable(meshParts.size()) + " mesh parts");
                return meshParts;
            }
        }
    }
}