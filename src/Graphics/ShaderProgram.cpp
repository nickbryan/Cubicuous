#include "ShaderProgram.h"

namespace Cubicuous {
    using namespace Debugging;

    namespace Graphics {

        ShaderProgram::ShaderProgram() {
            this->_checkError("Errors before create shader program");
            this->_shaderProgramID = glCreateProgram();

            if (this->_shaderProgramID == 0) {
                throw GraphicsException("Failed to create shader program");
            }
            else if (glIsProgram(this->_shaderProgramID) != GL_TRUE) {
                throw GraphicsException("Failed to create shader program, shader program is not a shader program");
            }

            this->_checkError("Failed to create shader program");
        }

        ShaderProgram::~ShaderProgram() {
            glDeleteProgram(this->_shaderProgramID);
        }

        void ShaderProgram::attachShader(const char *shaderFilePath, GLenum shaderType) {
            GLuint shader = this->_getShader(shaderFilePath, shaderType);
            glAttachShader(this->_shaderProgramID, shader);
            glDeleteShader(shader);
            this->_checkError("Failed to attach shader " + Logger::toLoggable(shaderFilePath));
        }

        void ShaderProgram::addVertexArray(VertexArray* vertexArray) {
            this->_vertexArrays.push_back(vertexArray);
        }

        void ShaderProgram::reloadActiveVertexArray() const {
            if(this->_activeVertexArray != nullptr) {
                this->_activeVertexArray->enable();
            }
        }

        void ShaderProgram::disableActiveVertexArray() {
            this->_activeVertexArray->disable();
            this->_activeVertexArray = nullptr;
        }

        void ShaderProgram::setActiveVertexArray(const char* name) {
            for(VertexArray* vertexArray : this->_vertexArrays) {
                if(vertexArray->getName() == name) {
                    this->_activeVertexArray = vertexArray;
                    vertexArray->enable();
                    break;
                }
            }
        }

        void ShaderProgram::bindOutput(const char* binding) {
            glBindFragDataLocation(this->_shaderProgramID, 0, binding);
            this->_checkError("Failed binding data location '" + Logger::toLoggable(binding) + "'");
        }

        void ShaderProgram::enable() {
            glLinkProgram(this->_shaderProgramID);
            this->_checkError("Failed linking shader program");
            glUseProgram(this->_shaderProgramID);
        }

        GLuint ShaderProgram::_getShader(const char *shaderFilePath, GLenum shaderType) {
            std::string shaderNameString = Logger::toLoggable(shaderFilePath);
            Logger::log("Shader Manager", "Making shader " + shaderNameString);

            /* Read file */
            Logger::log("Shader Manager", "Reading shader file");
            std::ifstream shaderFile;
            shaderFile.open(shaderFilePath, std::ios_base::in);

            if (!shaderFile) {
                throw GraphicsException("Shader file not found");
            }

            std::string line;
            std::string shaderData;
            while (std::getline(shaderFile, line)) {
                shaderData += line + NEWLINE;
            }

            shaderFile.close();

            /* Create shader */
            Logger::log("Shader Manager", "Compiling shader");
            GLuint shaderID = glCreateShader(shaderType);

            if (shaderID == 0) {
                throw GraphicsException("Failed to create shader, id 0 returned");
            }

            const char *shaderStr = shaderData.c_str();
            glShaderSource(shaderID, 1, &shaderStr, nullptr);
            glCompileShader(shaderID);

            /* Check compile status */
            GLint status;
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
            if (status != GL_TRUE) {
                GLint logLength;
                glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

                GLchar *infoLog = new GLchar[logLength + 1];
                glGetShaderInfoLog(shaderID, logLength, nullptr, infoLog);

                throw GraphicsException("Failed to compile shader: " + Logger::toLoggable(infoLog));
            }

            this->_checkError("Failed making shader program");
            return shaderID;
        }

        void ShaderProgram::_checkError(const char* strIfError) {
            GLenum error = glGetError();
            if(error != GL_NO_ERROR) {
                throw GraphicsException(Logger::toLoggable(strIfError) + ". Error: " + Logger::toLoggable(error) + ": "
                                      + Logger::toLoggable(glewGetErrorString(error)));
            }
        }
    }
}
