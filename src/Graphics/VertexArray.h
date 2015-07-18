#ifndef CUBICUOUS_VERTEXARRAY_H
#define CUBICUOUS_VERTEXARRAY_H

#include "../Debugging/Logger.h"
#include "GraphicsException.h"
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <string>

namespace Cubicuous {
    namespace Graphics {
        class VertexArray {
        private:
            GLuint        _id;
            const char*   _location;
            GLint         _size;
            GLenum        _type;
            GLboolean     _normalised;
            GLsizei       _stride;
            const GLvoid* _pointer;
            bool          _enabled = false;

        public:
            inline VertexArray(GLuint shaderProgramId, const char* location, GLint size, GLenum type, GLboolean normalised,
                               GLsizei stride, const GLvoid* pointer) {
                GLint attrId = glGetAttribLocation(shaderProgramId, location);

                if(attrId == -1) { //opengl only uses signed so it can return -1
                    throw GraphicsException("Failed to get attr location " + Debugging::Logger::toLoggable(location));
                }

                this->_id = (GLuint)attrId;
                this->_location = location;
                this->setAttrOptions(size, type, normalised, stride, pointer);
            }

            inline void setAttrOptions(GLint size, GLenum type, GLboolean normalised, GLsizei stride, const GLvoid* pointer) {
                this->_size = size;
                this->_type = type;
                this->_normalised = normalised;
                this->_stride = stride;
                this->_pointer = pointer;
            }

            inline void enable() {
                glEnableVertexAttribArray(this->_id);
                this->_setupAttr();
                this->_enabled = true;
            }

            inline bool isEnabled() const { return this->_enabled; }

            inline void disable() {
                if(this->_enabled) {
                    glDisableVertexAttribArray(this->_id);
                    this->_enabled = false;
                }
            }

            inline GLuint getID() { return this->_id; }

            inline const char* getName() { return this->_location; }

        private:
            inline void _setupAttr() const {
                glVertexAttribPointer(this->_id, this->_size, this->_type, this->_normalised, this->_stride, this->_pointer);
            }
        };
    }
}

#endif