#ifndef CUBICUOUS_SHADERMANAGER_H
#define CUBICUOUS_SHADERMANAGER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <initializer_list>
#include <fstream>

#include "Shader.h"
#include "../Debugging/Logger.h"

namespace Cubicuous {
    namespace Graphics {
        struct ShaderManager {
            static GLuint getShader(const char* shaderName, GLenum shaderType);
            static GLuint getShader(Shader& shader);

            static GLuint getShaderProgram(std::initializer_list<Shader> shaders,
                                           std::initializer_list<const char*> binds);

            static inline GLint getUniformLocation(GLuint shaderProgram, const GLchar* name) {
                return glGetUniformLocation(shaderProgram, name);
            }

            static inline void setUniform1f(GLuint shaderProgram, const GLchar* name, float value) {
                glUniform1f(ShaderManager::getUniformLocation(shaderProgram, name), value);
            }

            static inline void setUniform1fv(GLuint shaderProgram, const GLchar* name, float* value, int count)
            {
                glUniform1fv(ShaderManager::getUniformLocation(shaderProgram, name), count, value);
            }

            static inline void setUniform1i(GLuint shaderProgram, const GLchar* name, int value)
            {
                glUniform1i(ShaderManager::getUniformLocation(shaderProgram, name), value);
            }

            static inline void setUniform1iv(GLuint shaderProgram, const GLchar* name, int* value, int count)
            {
                glUniform1iv(ShaderManager::getUniformLocation(shaderProgram, name), count, value);
            }

            static inline void setUniform2f(GLuint shaderProgram, const GLchar* name, const glm::vec2& vector)
            {
                glUniform2f(ShaderManager::getUniformLocation(shaderProgram, name), vector.x, vector.y);
            }

            static inline void setUniform3f(GLuint shaderProgram, const GLchar* name, const glm::vec3& vector)
            {
                glUniform3f(ShaderManager::getUniformLocation(shaderProgram, name), vector.x, vector.y, vector.z);
            }

            static inline void setUniform4f(GLuint shaderProgram, const GLchar* name, const glm::vec4& vector)
            {
                glUniform4f(ShaderManager::getUniformLocation(shaderProgram, name), vector.x, vector.y, vector.z, vector.w);
            }

            static inline void setUniformMat4(GLuint shaderProgram, const GLchar* name, const glm::mat4& matrix)
            {
                glUniformMatrix4fv(ShaderManager::getUniformLocation(shaderProgram, name),
                                   1, GL_FALSE, glm::value_ptr(matrix));
            }

            static inline void enableShader(GLuint shaderProgram) {
                glUseProgram(shaderProgram);
            }

            static inline void disableShader() {
                glUseProgram(0);
            }

            static inline void destroyShader(GLuint shaderProgram) {
                glDeleteProgram(shaderProgram);
            }
        };
    }
}

#endif
