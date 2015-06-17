#ifndef CUBICUOUS_SHADERMANAGER_H
#define CUBICUOUS_SHADERMANAGER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <fstream>

#include "../Debugging/Logger.h"

namespace Cubicuous {
    namespace Graphics {
        class ShaderProgram {
        private:
            GLuint _shaderProgramID;
            GLint _VertexAttribArrayID;

        public:
            ShaderProgram();
            ~ShaderProgram();

            void attachShader(const char* shaderFilePath, GLenum shaderType);

            void bindFragDataLocation(const char* binding);

            void enable();

            void setVertexAttribArray(const char* location, GLint size, GLenum type, GLboolean normalised,
                                        GLsizei stride, const GLvoid* pointer);

            void disableVertexAttribArray();

            inline GLint getVertexAttribArray() { return this->_VertexAttribArrayID; }

            inline void disable() {
                glUseProgram(0);
            }

            inline void setUniform1f(const GLchar* name, float value) {
                glUniform1f(this->_getUniformLocation(name), value);
            }

            inline void setUniform1fv(const GLchar* name, float* value, int count)
            {
                glUniform1fv(this->_getUniformLocation(name), count, value);
            }

            inline void setUniform1i(const GLchar* name, int value)
            {
                glUniform1i(this->_getUniformLocation(name), value);
            }

            inline void setUniform1iv(const GLchar* name, int* value, int count)
            {
                glUniform1iv(this->_getUniformLocation(name), count, value);
            }

            inline void setUniform2f(const GLchar* name, const glm::vec2& vector)
            {
                glUniform2f(this->_getUniformLocation(name), vector.x, vector.y);
            }

            inline void setUniform3f(const GLchar* name, const glm::vec3& vector)
            {
                glUniform3f(this->_getUniformLocation(name), vector.x, vector.y, vector.z);
            }

            inline void setUniform4f(const GLchar* name, const glm::vec4& vector)
            {
                glUniform4f(this->_getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
            }

            inline void setUniformMat4(const GLchar* name, const glm::mat4& matrix)
            {
                glUniformMatrix4fv(this->_getUniformLocation(name),
                                   1, GL_FALSE, glm::value_ptr(matrix));
            }

        private:
            GLuint _getShader(const char *shaderFilePath, GLenum shaderType);

            inline GLint _getUniformLocation(const GLchar *name) {
                return glGetUniformLocation(this->_shaderProgramID, name);
            }
        };
    }
}

#endif
