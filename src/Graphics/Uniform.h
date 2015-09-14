#ifndef CUBICUOUS_UNIFORM_H
#define CUBICUOUS_UNIFORM_H

#include <functional>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "Exception.h"
#include "../Debugging/Logger.h"

namespace Cubicuous {
    namespace Graphics {
        class Uniform {
        private:
            GLint       _id;
            std::string _name;

            bool _keepValue = false;

            float* _valuePtr = nullptr;
            int    _count = -1;

            float  _value = -1.0f;

            int    _intValue = -1;

            int*   _intValuePtr = nullptr;

            glm::vec2 _vec2;
            glm::vec3 _vec3;
            glm::vec4 _vec4;
            glm::mat4 _mat4;

        public:
            inline Uniform(GLuint shaderProgramID, const char* name) {
                this->_id = glGetUniformLocation(shaderProgramID, name);

                if (this->_id == -1) {
                    throw Exception("Uniform location " + Debugging::Logger::toLoggable(name) + " not found");
                }

                GLenum error = glGetError();
                if (error != GL_NO_ERROR) {
                    throw Exception(
                            "Failed to get uniform location " + Debugging::Logger::toLoggable(name) + ", error: " +
                            Debugging::Logger::toLoggable(error));
                }

                this->_vec2 = glm::vec2();
                this->_vec3 = glm::vec3();
                this->_vec4 = glm::vec4();
                this->_mat4 = glm::mat4();
                this->_name = std::string(name);
            }

            inline void keepValue() { this->_keepValue = true; }

            inline bool isKeepingValue() { return this->_keepValue; }

            inline void stopKeepingValue() { this->_keepValue = false; }

            inline void revertValue() {
                if(this->_value != -1.0f) {
                    this->update(this->_value);
                }
                else if(this->_valuePtr != nullptr) {
                    this->update(this->_valuePtr, this->_count);
                }
                else if(this->_intValue != -1) {
                    this->update(this->_intValue);
                }
                else if(this->_intValuePtr != nullptr) {
                    this->update(this->_intValuePtr, this->_count);
                }
                else if(this->_vec2 != glm::vec2()) {
                    this->update(this->_vec2);
                }
                else if(this->_vec3 != glm::vec3()) {
                    this->update(this->_vec3);
                }
                else if(this->_vec4 != glm::vec4()) {
                    this->update(this->_vec4);
                }
                else if(this->_mat4 != glm::mat4()) {
                    this->update(this->_mat4);
                }
            }

            inline GLint getID() const { return this->_id; }

            inline std::string getName() const { return this->_name; }

            inline void update(float value) {
                if(this->_keepValue) {
                    this->_clearKeptValues();
                    this->_value = value;
                }

                glUniform1f(this->_id, value);
            }

            inline void update(float* value, int count) {
                if(this->_keepValue) {
                    this->_clearKeptValues();
                    this->_valuePtr = value;
                    this->_count = count;
                }

                glUniform1fv(this->_id, count, value);
            }

            inline void update(int value) {
                if(this->_keepValue) {
                    this->_clearKeptValues();
                    this->_intValue = value;
                }

                glUniform1i(this->_id, value);
            }

            inline void update(int* value, int count) {
                if(this->_keepValue) {
                    this->_clearKeptValues();
                    this->_intValuePtr = value;
                    this->_count = count;
                }

                glUniform1iv(this->_id, count, value);
            }

            inline void update(const glm::vec2& vector) {
                if(this->_keepValue) {
                    this->_clearKeptValues();
                    this->_vec2 = vector;
                }

                glUniform2f(this->_id, vector.x, vector.y);
            }

            inline void update(const glm::vec3& vector) {
                if(this->_keepValue) {
                    this->_clearKeptValues();
                    this->_vec3 = vector;
                }

                glUniform3f(this->_id, vector.x, vector.y, vector.z);
            }

            inline void update(const glm::vec4& vector) {
                if(this->_keepValue) {
                    this->_clearKeptValues();
                    this->_vec4 = vector;
                }

                glUniform4f(this->_id, vector.x, vector.y, vector.z, vector.w);
            }

            inline void update(const glm::mat4& matrix) {
                if(this->_keepValue) {
                    this->_clearKeptValues();
                    this->_mat4 = matrix;
                }

                glUniformMatrix4fv(this->_id, 1, GL_FALSE, glm::value_ptr(matrix));
            }

        private:
            void _clearKeptValues() {
                this->_valuePtr = nullptr;
                this->_value = -1.0f;
                this->_intValue = -1;
                this->_count = -1;
                this->_intValuePtr = nullptr;
                this->_vec2 = glm::vec2();
                this->_vec3 = glm::vec3();
                this->_vec4 = glm::vec4();
                this->_mat4 = glm::mat4();
            }
        };
    }
}

#endif