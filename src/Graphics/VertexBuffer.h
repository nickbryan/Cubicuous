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

                bool     _keepValue;
                GLfloat* _previousValue;
                GLsizei  _previousCount;
                GLfloat* _value;
                GLsizei  _count;

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

                inline void keepValue() {
                    this->_keepValue = true;
                }

                inline void stopKeepingValue() {
                    this->_keepValue = false;
                }

                inline void revertValue() {
                    this->updateData(this->_previousValue, this->_previousCount);
                }

                inline GLuint getBufferID() const { return this->_bufferID; }

                inline void updateData(GLfloat* data, GLsizei count) {
                    if(this->_keepValue) {
                        this->_previousValue = this->_value;
                        this->_previousCount = this->_count;
                        this->_value = data;
                        this->_count = count;
                    }

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