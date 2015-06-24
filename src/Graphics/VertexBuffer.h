#ifndef CUBICUOUS_VERTEXBUFFER_H
#define CUBICUOUS_VERTEXBUFFER_H

#include <GL/glew.h>

namespace Cubicuous {
    namespace Graphics {
        class VertexBuffer {
            private:
                GLuint _bufferID;
                GLenum _type;
                GLenum _storageMode;

            public:
                VertexBuffer(GLenum type, GLenum storageMode) {
                    this->_type = type;
                    this->_storageMode = storageMode;

                    glGenBuffers(1, &this->_bufferID);
                    glBindBuffer(this->_type, this->_bufferID);

                    GLenum error = glGetError();
                    if(error != GL_NO_ERROR) {
                        Debugging::Logger::log("Failed generating vertex buffer: " + Debugging::Logger::toLoggable(error));
                    }
                }

                VertexBuffer(GLenum type) : VertexBuffer(type, GL_STATIC_DRAW) {}

                inline VertexBuffer(GLenum type, GLenum storageMode, GLuint bufferId) {
                    this->_bufferID = bufferId;
                    this->_type = type;
                    this->_storageMode = storageMode;
                }

                inline ~VertexBuffer() {
                    glDeleteBuffers(1, &this->_bufferID);
                }

                inline GLuint getBufferID() const { return this->_bufferID; }

                inline void updateData(GLfloat* data, GLsizei count) {
                    glBindBuffer(this->_type, this->_bufferID);
                    GLenum error = glGetError();
                    if(error != GL_NO_ERROR) {
                        Debugging::Logger::log("Failed binding buffer data: " + Debugging::Logger::toLoggable(error));
                    }

                    glBufferData(this->_type, count * sizeof(GLfloat), data, this->_storageMode);
                    error = glGetError();
                    if(error != GL_NO_ERROR) {
                        Debugging::Logger::log("Failed updating buffer data: " + Debugging::Logger::toLoggable(error));
                    }
                }
        };
    }
}
#endif