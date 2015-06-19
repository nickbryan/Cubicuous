#ifndef CUBICUOUS_SHADEREXCEPTION_H
#define CUBICUOUS_SHADEREXCEPTION_H

#include <exception>
#include <string.h>

namespace Cubicuous {
    namespace Graphics {
        class ShaderException : public std::exception {
        private:
            std::string _what;

        public:
            ShaderException(const char* what) {
                this->_what = std::string(what);
            }
            ShaderException(std::string what) {
                this->_what = what;
            }

            virtual ~ShaderException() throw() {

            }

            inline virtual const char* what() const throw() override {
                return this->_what.c_str();
            }
        };
    };
};

#endif