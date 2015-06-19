#include "ShaderProgram.h"

namespace Cubicuous {
    using namespace Debugging;

    namespace Graphics {

        ShaderProgram::ShaderProgram() {
            this->_checkError("Errors before create shader program");
            this->_shaderProgramID = glCreateProgram();

            if (this->_shaderProgramID == 0) {
                throw ShaderException("Failed to create shader program");
            }
            else if (glIsProgram(this->_shaderProgramID) != GL_TRUE) {
                throw ShaderException("Failed to create shader program, shader program is not a shader program");
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

        void ShaderProgram::bindFragDataLocation(const char *binding) {
            glBindFragDataLocation(this->_shaderProgramID, 0, binding);
            this->_checkError("Failed binding data location '" + Logger::toLoggable(binding) + "'");
        }

        void ShaderProgram::enable() {
            glLinkProgram(this->_shaderProgramID);
            this->_checkError("Failed linking shader program");
            glUseProgram(this->_shaderProgramID);
        }

        void ShaderProgram::setVertexAttribArray(const char *location, GLint size, GLenum type, GLboolean normalised,
                                                   GLsizei stride, const GLvoid *pointer) {
            GLint attrId = glGetAttribLocation(this->_shaderProgramID, location);

            std::string locationStr = Logger::toLoggable(location);
            if(attrId == -1) { //opengl only uses signed so it can return -1
                throw ShaderException("Failed to get attr location" + locationStr);
            }
            this->_checkError("Failed to get attrib location " + locationStr);

            this->_vertexAttribArrayID = (GLuint)attrId;
            glEnableVertexAttribArray(this->_vertexAttribArrayID);
            this->_checkError("Failed to enable attrib " + locationStr);
            glVertexAttribPointer(this->_vertexAttribArrayID, size, type, normalised, stride, pointer);
            this->_checkError("Failed to link attrib " + locationStr + " to program");
        }

        void ShaderProgram::disableVertexAttribArray() {
            glDisableVertexAttribArray(this->_vertexAttribArrayID);
            this->_checkError("Failed to disable active vertex attribute");
        }

        GLuint ShaderProgram::_getShader(const char *shaderFilePath, GLenum shaderType) {
            std::string shaderNameString = Logger::toLoggable(shaderFilePath);
            Logger::log("Shader Manager", "Making shader " + shaderNameString);

            /* Read file */
            Logger::log("Shader Manager", "Reading shader file");
            std::ifstream shaderFile;
            shaderFile.open(shaderFilePath, std::ios_base::in);

            if (!shaderFile) {
                throw ShaderException("Shader file not found");
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
                throw ShaderException("Failed to create shader, id 0 returned");
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

                throw ShaderException("Failed to compile shader: " + Logger::toLoggable(infoLog));
            }

            this->_checkError("Failed making shader program");
            return shaderID;
        }

        void ShaderProgram::_checkError(const char* strIfError) {
            GLenum error = glGetError();
            if(error != GL_NO_ERROR) {
                throw ShaderException(Logger::toLoggable(strIfError) + ". Error: " + Logger::toLoggable(error) + ": "
                                      + Logger::toLoggable(glewGetErrorString(error)));
            }
        }
    }
}
