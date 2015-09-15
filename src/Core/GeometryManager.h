#ifndef CUBICUOUS_IGEOMETRYMANAGER_H
#define CUBICUOUS_IGEOMETRYMANAGER_H

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <GL/glew.h>
#include "../Graphics/Uniform.h"
#include "../Graphics/VertexBuffer.h"
#include "Exception.h"

namespace Cubicuous {
    namespace Core {
        class GeometryManager {
        private:
            Graphics::Uniform* _verticesUniform = nullptr;
            Graphics::Uniform* _colorUniform    = nullptr;
            Graphics::VertexBuffer* _verticesBuffer = nullptr;
            Graphics::VertexBuffer* _colorBuffer    = nullptr;

        public:
            //Shorthands for boolean based constructors
            inline GeometryManager(Game* game, std::string verticesName) : GeometryManager(game, verticesName, false) {};
            inline GeometryManager(Game* game, std::string verticesName, bool usesUniform) : GeometryManager(game, verticesName, "", usesUniform) {};
            inline GeometryManager(Game* game, std::string verticesName, std::string colorName) : GeometryManager(game, verticesName, colorName, false) {};

            //Short hands for full constructor
            inline GeometryManager(Game* game, std::string verticesName, std::string colorName, bool usesUniform) :
                    GeometryManager(game, verticesName, colorName, usesUniform, usesUniform) {};
            inline GeometryManager(Game* game, std::string verticesName, std::string colorName, bool verticesUsesUniform, bool colorUsesUniform) :
                    GeometryManager(game, verticesUsesUniform ? "" : verticesName,
                                          colorUsesUniform    ? "" : colorName,
                                          verticesUsesUniform ? verticesName : "",
                                          colorUsesUniform    ? colorName : "") {};

            GeometryManager(Game* game, std::string verticesBufferName, std::string colorBufferName, std::string verticesUniformName, std::string colorUniformName);

            virtual void updateVertices(GLfloat *vertices, GLsizei count);

            virtual void updateVertices(glm::vec3 vertex);

            virtual void updateColor(GLfloat* colors, GLsizei count);

            inline void updateColor(glm::vec4 color) { this->updateColor(color.x, color.y, color.z, color.w); };
            inline void updateColor(glm::vec3 color) { this->updateColor(color.x, color.y, color.z, 1.0f); };
            virtual void updateColor(float r, float g, float b, float a);

            //These methods with size have built in backups so if we can't use uniform we fill a buffer and use that
            inline void updateColor(glm::vec4 color, GLsizei size) { this->updateColor(color.x, color.y, color.z, color.w, size); };
            inline void updateColor(glm::vec3 color, GLsizei size) { this->updateColor(color.x, color.y, color.z, 1.0f, size); };
            virtual void updateColor(float r, float g, float b, float a, GLsizei size);

            bool isVerticesUniformOnly() const {
                return this->_verticesBuffer != nullptr;
            }

            bool isColorUniformOnly() const {
                return this->_colorBuffer != nullptr;
            }

            bool isUniformOnly() const {
                return this->isVerticesUniformOnly() && this->isColorUniformOnly();
            }
        };
    }
}

#endif