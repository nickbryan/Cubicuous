#include "../Game.h"

namespace Cubicuous {
    namespace Core {
        GeometryManager::GeometryManager(Game* game, std::string verticesBufferName, std::string colorBufferName,
                                         std::string verticesUniformName, std::string colorUniformName) {
            if(verticesBufferName != "") {
                this->_verticesBuffer = game->getVertexBuffer(verticesBufferName);
            }

            if(colorBufferName != "") {
                this->_colorBuffer = game->getVertexBuffer(colorBufferName);
            }

            if(verticesUniformName != "") {
                this->_verticesUniform = game->getShaderProgram()->getCachedUniform(verticesUniformName);
            }

            if(colorUniformName != "") {
                this->_colorUniform = game->getShaderProgram()->getCachedUniform(colorUniformName);
            }
        }

        void GeometryManager::updateVertices(GLfloat *vertices, GLsizei count) {
            this->_verticesBuffer->update(vertices, count);
        }

        void GeometryManager::updateColor(GLfloat *colors, GLsizei count) {
            this->_colorBuffer->update(colors, count);
        }

        void GeometryManager::updateVertices(glm::vec3 vertex) {
            this->_verticesUniform->update(vertex);
        }

        void GeometryManager::updateColor(float r, float g, float b) {
            this->_colorUniform->update(glm::vec3(r,g,b));
        }
    }
}