#include "ShaderProgram.h"



namespace Cubicuous {
    using namespace Debugging;

    namespace Graphics {

        ShaderProgram::ShaderProgram() {
            this->_shaderProgramID = glCreateProgram();

            GLenum error = glGetError();

            if (this->_shaderProgramID == 0) {
                Logger::log("Shader Manager", "Failed to create shader program");
            }
            else if (glIsProgram(this->_shaderProgramID) != GL_TRUE) {
                Logger::log("Shader Manager", "Failed to create shader program");
            }
        }

        ShaderProgram::~ShaderProgram() {
            glDeleteProgram(this->_shaderProgramID);
        }

        void ShaderProgram::attachShader(const char *shaderFilePath, GLenum shaderType) {
            GLuint shader = this->_getShader(shaderFilePath, shaderType);
            glAttachShader(this->_shaderProgramID, shader);
            glDeleteShader(shader);

            GLenum error = glGetError();
            if(error != GL_NO_ERROR) {
                Logger::log("Shader Manager", "Failed attaching shader, error " +
                        Logger::toLoggable(error) + ": " + Logger::toLoggable(glewGetErrorString(error)));
            }
        }

        void ShaderProgram::bindFragDataLocation(const char *binding) {
            glBindFragDataLocation(this->_shaderProgramID, 0, binding);

            GLenum error = glGetError();
            if(error != GL_NO_ERROR) {
                Logger::log("Shader Manager", "Failed binding data location, error " +
                                              Logger::toLoggable(error) + ": " + Logger::toLoggable(glewGetErrorString(error)));
            }
        }

        void ShaderProgram::enable() {
            glLinkProgram(this->_shaderProgramID);

            GLenum error = glGetError();
            if(error != GL_NO_ERROR) {
                Logger::log("Shader Manager", "Failed linking shader program, error " +
                                              Logger::toLoggable(error) + ": " + Logger::toLoggable(glewGetErrorString(error)));
            }

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
                Logger::log("Shader Manager", shaderNameString + " not found");
                return 0;
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
                Logger::log("Shader Manager", "Failed to create shader for " + shaderNameString);
                return 0;
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

                Logger::log("Shader Manager", shaderNameString + " failed to compile: " + infoLog);
                return 0;
            }

            GLenum error = glGetError();
            if(error != GL_NO_ERROR) {
                Logger::log("Shader Manager", "Failed making shader program, error "
                                    + Logger::toLoggable(error) + ": "
                                    + Logger::toLoggable(glewGetErrorString(error)));
                return 0;
            }

            return shaderID;
        }
    }
}
