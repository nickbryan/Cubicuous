#ifndef CUBICUOUS_SHADERMANAGER_H
#define CUBICUOUS_SHADERMANAGER_H

#include <GL/glew.h>
#include <initializer_list>
#include <fstream>

#include "Shader.h"
#include "../Debugging/Logger.h"

namespace Cubicuous {
    namespace Graphics {
        class ShaderManager {
        public:
            static GLuint getShader(const char* shaderName, GLenum shaderType);
            static GLuint getShader(Shader& shader);

            static GLuint getShaderProgram(std::initializer_list<Shader> shaders,
                                           std::initializer_list<const char*> binds);
        };
    }
}

#endif
