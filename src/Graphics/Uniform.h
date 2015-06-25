#ifndef CUBICUOUS_UNIFORM_H
#define CUBICUOUS_UNIFORM_H

#include <functional>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "GraphicsException.h"
#include "../Debugging/Logger.h"

namespace Cubicuous {
    namespace Graphics {
        class Uniform {
        private:
            GLint       _id;
            std::string _name;

        public:
            inline Uniform(GLuint shaderProgramID, const char* name) {
                this->_id = glGetUniformLocation(shaderProgramID, name);

                if (this->_id == -1) {
                    throw GraphicsException("Uniform location " + Debugging::Logger::toLoggable(name) + " not found");
                }

                GLenum error = glGetError();
                if (error != GL_NO_ERROR) {
                    throw GraphicsException(
                            "Failed to get uniform location " + Debugging::Logger::toLoggable(name) + ", error: " +
                            Debugging::Logger::toLoggable(error));
                }

                this->_name = std::string(name);
            }

            inline GLint getID() const { return this->_id; }

            inline std::string getName() const { return this->_name; }

            inline void update(float value) {
                glUniform1f(this->_id, value);
            }

            inline void update(float* value, int count) {
                glUniform1fv(this->_id, count, value);
            }

            inline void update(int value) {
                glUniform1i(this->_id, value);
            }

            inline void update(int* value, int count) {
                glUniform1iv(this->_id, count, value);
            }

            inline void update(const glm::vec2& vector) {
                glUniform2f(this->_id, vector.x, vector.y);
            }

            inline void update(const glm::vec3& vector) {
                glUniform3f(this->_id, vector.x, vector.y, vector.z);
            }

            inline void update(const glm::vec4& vector) {
                glUniform4f(this->_id, vector.x, vector.y, vector.z, vector.w);
            }

            inline void update(const glm::mat4& matrix) {
                glUniformMatrix4fv(this->_id, 1, GL_FALSE, glm::value_ptr(matrix));
            }
        };
    }
}

#endif