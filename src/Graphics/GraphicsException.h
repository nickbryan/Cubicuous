#ifndef CUBICUOUS_SHADEREXCEPTION_H
#define CUBICUOUS_SHADEREXCEPTION_H

#include <exception>
#include <string.h>

namespace Cubicuous {
    namespace Graphics {
        class GraphicsException : public std::exception {
        private:
            std::string _what;

        public:
            GraphicsException(const char* what) {
                this->_what = std::string(what);
            }
            GraphicsException(std::string what) {
                this->_what = what;
            }

            virtual ~GraphicsException() throw() {

            }

            inline virtual const char* what() const throw() override {
                return this->_what.c_str();
            }
        };
    };
};

#endif