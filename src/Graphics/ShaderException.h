#ifndef CUBICUOUS_SHADEREXCEPTION_H
#define CUBICUOUS_SHADEREXCEPTION_H

#include <exception>

namespace Cubicuous {
    namespace Graphics {
        class ShaderException : public std::exception {
        private:
            const char* _what;

        public:
            ShaderException(const char* what) {
                this->_what = what;
            }
            ShaderException(std::string what) {
                this->_what = what.c_str();
            }

            virtual ~ShaderException() throw() {

            }

            inline virtual const char* what() const throw() override {
                return this->_what;
            }
        };
    };
};

#endif