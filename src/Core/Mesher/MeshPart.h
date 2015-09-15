#ifndef CUBICUOUS_MESHPART_H
#define CUBICUOUS_MESHPART_H

#include <GL/glew.h>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <vector>

namespace Cubicuous {
    namespace Graphics {
        namespace Renderer {
            class IRenderer;
        }
    }

    namespace Core {
        namespace Mesher {
            class MeshPart {
            private:
                Graphics::Renderer::IRenderer* _renderer = nullptr;
                std::vector<glm::vec3>         _vertices;
                GLsizei                        _floatCount = 0;

            public:
                MeshPart(Graphics::Renderer::IRenderer* type) : _renderer(type) {}

                MeshPart(Graphics::Renderer::IRenderer* type, std::vector<glm::vec3> vertices) : _renderer(type), _vertices(vertices) {}

                void setVertex(int position, glm::vec3 vertex) {
                    this->_vertices[position] = vertex;
                }

                inline Graphics::Renderer::IRenderer* getRenderer() const {
                    return this->_renderer;
                }

                std::vector<glm::vec3> getVertices() const { return this->_vertices; }

                GLfloat* getVerticesAsFloats();

                inline GLsizei getLastVerticesCount() const {
                    return this->_floatCount + 1;
                }

                void render();
            };
        }
    }
}

#endif