#include "ShaderManager.h"



namespace Cubicuous {
    using namespace Debugging;

    namespace Graphics {
        GLuint ShaderManager::getShader(Shader &shader) {
            return ShaderManager::getShader(shader.file, shader.type);
        }

        GLuint ShaderManager::getShader(const char *shaderName, GLenum shaderType) {
            std::string shaderNameString = Logger::toLoggable(shaderName);

            Logger::log("Shader Manager", "Making shader " + shaderNameString);

            /* Read file */
            Logger::log("Shader Manager", "Reading shader file");
            std::ifstream shaderFile;
            shaderFile.open(shaderName, std::ios_base::in);

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
            GLuint shader = glCreateShader(shaderType);

            if (shader == 0) {
                Logger::log("Shader Manager", "Failed to create shader for " + shaderNameString);
                return 0;
            }

            const char *shaderStr = shaderData.c_str();

            glShaderSource(shader, 1, &shaderStr, nullptr);
            glCompileShader(shader);

            /* Check compile status */
            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (status != GL_TRUE) {
                GLint logLength;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

                GLchar *infoLog = new GLchar[logLength + 1];
                glGetShaderInfoLog(shader, logLength, nullptr, infoLog);

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

            return shader;
        }

        GLuint ShaderManager::getShaderProgram(std::initializer_list<Shader> shaders,
                                               std::initializer_list<const char *> binds) {
            /* Create the shader program */
            GLuint shaderProgram = glCreateProgram();
            GLenum error = glGetError();

            if (shaderProgram == 0) {
                Logger::log("Shader Manager", "Failed to create shader program");
                return 0;
            }
            else if (glIsProgram(shaderProgram) != GL_TRUE) {
                Logger::log("Shader Manager", "Failed to create shader program");
                return 0;
            }

            /* Compile & attach the shaders */
            for(Shader shader : shaders) {
                GLuint glShader = getShader(shader);

                if (glShader == 0) {
                    Logger::log("Shader Manager", "Failed to load shader " + Logger::toLoggable(shader.file));
                    return 0;
                }

                Logger::log("Shader Manager", "Attaching shader " + Logger::toLoggable(shader.file));
                glAttachShader(shaderProgram, glShader);
                glDeleteShader(glShader);

                error = glGetError();
                if(error != GL_NO_ERROR) {
                    Logger::log("Shader Manager", "Failed attaching shader, error "
                                + Logger::toLoggable(error) + ": " + Logger::toLoggable(glewGetErrorString(error)));
                    return 0;
                }
            }

            /* Bind */
            for(const char* bind : binds) {
                Logger::log("Shader Manager", "Binding data location " + Logger::toLoggable(bind));
                glBindFragDataLocation(shaderProgram, 0, bind);

                error = glGetError();
                if(error != GL_NO_ERROR) {
                    Logger::log("Shader Manager", "Failed binding data location, error "
                                + Logger::toLoggable(error) + ": " + Logger::toLoggable(glewGetErrorString(error)));
                    return 0;
                }
            }

            /* Link to opengl */
            glLinkProgram(shaderProgram);
            error = glGetError();
            if(error != GL_NO_ERROR) {
                Logger::log("Shader Manager", "Failed linking shader program, error "
                            + Logger::toLoggable(error) + ": " + Logger::toLoggable(glewGetErrorString(error)));
                return 0;
            }

            return shaderProgram;
        }
    }
}
