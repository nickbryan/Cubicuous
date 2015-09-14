#ifndef CUBICUOUS_GRAPHICSEXCEPTION_H
#define CUBICUOUS_GRAPHICSEXCEPTION_H

#include <exception>
#include <string>
#include <sstream>
#include <iostream>

namespace Cubicuous {
    namespace Graphics {
        class Exception : public std::exception {
        private:
            std::string _what;

        public:
            Exception(const char* what) {
                this->_what = std::string(what);
            }
            Exception(std::string what) {
                this->_what = what;
            }

            virtual ~Exception() throw() {

            }

            inline virtual const char* what() const throw() override {
                return this->_what.c_str();
            }
        };
    };
};

#endif