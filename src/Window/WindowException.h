#ifndef CUBICUOUS_WINDOWEXCEPTION_H
#define CUBICUOUS_WINDOWEXCEPTION_H

#include <exception>
#include <string.h>

namespace Cubicuous {
    namespace Window {
        class WindowException : public std::exception {
        private:
            std::string _what;

        public:
            WindowException(const char* what) {
                this->_what = std::string(what);
            }
            WindowException(std::string what) {
                this->_what = what;
            }

            virtual ~WindowException() throw() {

            }

            inline virtual const char* what() const throw() override {
                return this->_what.c_str();
            }
        };
    };
};

#endif