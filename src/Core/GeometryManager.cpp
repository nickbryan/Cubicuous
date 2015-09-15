#include "../Game.h"

namespace Cubicuous {
    namespace Core {
        GeometryManager::GeometryManager(Game* game, std::string verticesBufferName, std::string colorBufferName,
                                         std::string verticesUniformName, std::string colorUniformName) {
            if(verticesBufferName != "") {
                Debugging::Logger::log("Geometry Manager", "Loading vertices buffer '" + verticesBufferName + "'");
                this->_verticesBuffer = game->getVertexBuffer(verticesBufferName);
            }

            if(colorBufferName != "") {
                Debugging::Logger::log("Geometry Manager", "Loading color buffer '" + colorBufferName + "'");
                this->_colorBuffer = game->getVertexBuffer(colorBufferName);
            }

            if(verticesUniformName != "") {
                Debugging::Logger::log("Geometry Manager", "Loading vertices uniform '" + verticesUniformName + "'");
                this->_verticesUniform = game->getShaderProgram()->getCachedUniform(verticesUniformName);
            }

            if(colorUniformName != "") {
                Debugging::Logger::log("Geometry Manager", "Loading color uniform '" + colorUniformName + "'");
                this->_colorUniform = game->getShaderProgram()->getCachedUniform(colorUniformName);
            }
        }

        void GeometryManager::updateVertices(GLfloat *vertices, GLsizei count) {
            if(this->_verticesBuffer == nullptr) {
                throw Exception("Called VertexArray based updateVertices when not setup for VertexArray usage");
            }

            this->_verticesBuffer->update(vertices, count);
        }

        void GeometryManager::updateColor(GLfloat *colors, GLsizei count) {
            if(this->_colorBuffer == nullptr) {
                throw Exception("Called VertexArray based updateColor when not setup for VertexArray usage");
            }

            this->_colorBuffer->update(colors, count);
        }

        void GeometryManager::updateVertices(glm::vec3 vertex) {
            if(this->_verticesUniform == nullptr) {
                throw Exception("Called Uniform based updateVertices when not setup for Uniform usage");
            }

            this->_verticesUniform->update(vertex);
        }

        void GeometryManager::updateColor(float r, float g, float b, float a) {
            if(this->_colorUniform == nullptr) {
                throw Exception("Called Uniform based updateColor when not setup for Uniform usage");
            }

            this->_colorUniform->update(glm::vec4(r,g,b,a));
        }

        void GeometryManager::updateColor(float r, float g, float b, float a, GLsizei size) {
            if(this->_colorUniform != nullptr) {
                this->_colorUniform->update(glm::vec4(r, g, b, a));
            }
            else if(this->_colorBuffer != nullptr) { //TODO: Test this, should fill an array with the rgba values so every point is coloured this rgba.
                GLfloat *colorFloats = new GLfloat[size * 4];

                for(int i = 0; i < size * 4; i++) {
                    colorFloats[i] = r;
                    colorFloats[++i] = g;
                    colorFloats[++i] = b;
                    colorFloats[++i] = a;
                }

                this->_colorBuffer->update(colorFloats, size * 4);
            }
            else {
                throw Exception("Called Uniform based updateColor when not setup for Uniform usage, also the Buffer version is not setup so it cannot be used instead");
            }
        }
    }
}