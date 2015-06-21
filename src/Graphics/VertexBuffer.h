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
                }

                VertexBuffer(GLenum type) : VertexBuffer(type, GL_STATIC_DRAW) {}

                inline VertexBuffer(GLenum type, GLenum storageMode, GLuint bufferId) {
                    this->_bufferID = bufferId;
                }

                inline ~VertexBuffer() {
                    glDeleteBuffers(1, &this->_bufferID);
                }

                inline GLuint getBufferID() const { return this->_bufferID; }

                inline void updateData(const void* data) {
                    glBindBuffer(GL_ARRAY_BUFFER, this->_bufferID);
                    glBufferData(this->_type, sizeof(data), data, this->_storageMode);

                    GLenum error = glGetError();
                    if(error != GL_NO_ERROR) {
                        Debugging::Logger::log("Failed updating buffer data" + Debugging::Logger::toLoggable(error));
                    }
                }
        };
    }
}
#endif