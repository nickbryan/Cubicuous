#ifndef CUBICUOUS_SHADER_H
#define CUBICUOUS_SHADER_H

#include <GL/glew.h>

namespace Cubicuous {
    namespace Graphics {

        struct Shader {
            const char* file;
            GLenum type;

            Shader(const char* file, GLenum type) {
                this->file = file;
                this->type = type;
            }
        };
    }
}

#endif
