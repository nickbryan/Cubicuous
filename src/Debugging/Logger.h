#ifndef CUBICUOUS_LOGGER_H
#define CUBICUOUS_LOGGER_H

#include <sstream>
#include <string>
#include <iostream>
#include <GL/glew.h>

namespace Cubicuous {
    namespace Debugging {
    #ifdef _WIN32
        #define NEWLINE "\r\n"
    #elif defined macintosh // OS 9
        #define NEWLINE "\r"
    #else
    #define NEWLINE "\n" // Mac OS X uses \n
    #endif

        class Logger {
        public:
            static void log(std::string str);

            static void log(const char *str);

            static void log(const char *category, const char *str);

            static void log(std::string category, std::string str);

            static std::string toLoggable(const GLubyte *gluByte);

            static std::string toLoggable(const char *chars);

            template<typename T>
            static std::string toLoggable(const T &n) {
                //mingw32 has a bug that stops std::to_string working so implement our self
                std::ostringstream stm;
                stm << n;
                return stm.str();
            }
        };
    }
}


#endif