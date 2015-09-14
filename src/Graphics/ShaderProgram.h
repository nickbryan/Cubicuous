#ifndef CUBICUOUS_SHADERPROGRAM_H
#define CUBICUOUS_SHADERPROGRAM_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <fstream>

#include "../Debugging/Logger.h"
#include "Exception.h"
#include "VertexArray.h"
#include "Uniform.h"

namespace Cubicuous {
    namespace Graphics {
        class ShaderProgram {
        private:
            GLuint                    _shaderProgramID;
            VertexArray*              _activeVertexArray = nullptr;
            std::vector<VertexArray*> _vertexArrays;
            std::vector<Uniform*>     _uniforms;

        public:
            ShaderProgram();
            ~ShaderProgram();

            //shaders
            void attachShader(const char* shaderFilePath, GLenum shaderType);

            void bindOutput(const char* binding);

            //shader program
            void enable();

            inline GLuint getID() const { return this->_shaderProgramID; }

            inline void disable() {
                this->disableActiveVertexArray();
                glUseProgram(0);
            }

            //uniforms
            Uniform* getCachedUniform(const char* name) const;
            inline Uniform* getCachedUniform(std::string name) const { return this->getCachedUniform(name.c_str()); };

            inline Uniform* cacheUniform(const char* name) {
                Uniform* uniform = new Uniform(this->_shaderProgramID, name);
                this->cacheUniform(uniform);
                return uniform;
            }
            inline void cacheUniform(Uniform* uniform) {
                this->_uniforms.push_back(uniform);
                Debugging::Logger::log("Shader Program", "Cached uniform " + uniform->getName());
            }

            //vertex arrays
            inline VertexArray* addVertexArray(const char* location, GLint size, GLenum type, GLboolean normalised,
                                       GLsizei stride, const GLvoid* pointer) {
               VertexArray* vertexArray = new VertexArray(this->_shaderProgramID, location, size, type, normalised, stride, pointer);
               this->addVertexArray(vertexArray);
               return vertexArray;
            }

            void addVertexArray(VertexArray* vertexArray);

            void reloadActiveVertexArray() const;

            inline VertexArray* getActiveVertexArray() const { return this->_activeVertexArray; }

            VertexArray* getVertexArray(const char* name) const;

            inline VertexArray* getVertexArray(std::string name) const { return this->getVertexArray(name.c_str()); };

            void setActiveVertexArray(const char* name);

            void disableActiveVertexArray();

        private:
            GLuint _getShader(const char *shaderFilePath, GLenum shaderType);

            void _checkError(const char* strIfError);
            inline void _checkError(std::string strIfError) {
                this->_checkError(strIfError.c_str());
            };
        };
    }
}

#endif