#ifndef CUBICUOUS_IRENDERER_H
#define CUBICUOUS_IRENDERER_H

#include <GL/glew.h>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <vector>
#include "../../Core/Mesher/MeshPart.h"

namespace Cubicuous {
    class Game;

    namespace Graphics {
        namespace Renderer {
            class IRenderer {
            protected:
                Game* _game;

            public:
                IRenderer(Game* game) : _game(game) {}

                virtual void render(GLfloat* vertices, GLsizei size) = 0;

                inline void render(std::vector<glm::vec3> triangles) {
                    GLsizei size = -1;
                    GLfloat* vertices = new GLfloat[triangles.size() * 3];

                    for(glm::vec3 vertex : triangles) {
                        vertices[++size] = vertex.x;
                        vertices[++size] = vertex.y;
                        vertices[++size] = vertex.z;
                    }

                    this->render(vertices, size);
                }

                inline void render(std::vector<Core::Mesher::MeshPart*> meshParts) {
                    std::vector<glm::vec3> triangles;

                    for(Core::Mesher::MeshPart *part : meshParts) {
                        for(glm::vec3 vertex : part->getVertices()) {
                            triangles.push_back(vertex);
                        }
                    }

                    this->render(triangles);
                }

                virtual bool isSameAs(IRenderer *renderer) = 0;
            };
        }
    }
}

#endif