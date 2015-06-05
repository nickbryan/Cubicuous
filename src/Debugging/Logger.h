#ifndef CUBICUOUS_LOGGER_H
#define CUBICUOUS_LOGGER_H

#include <string>
#include <iostream>
#include <GL/glew.h>

namespace Cubicuous {
    namespace Debugging {
        class Logger {
        public:
	        static void log(std::string str);

	        static void log(const char *str);

	        static void log(const char *category, const char *str);

	        static void log(std::string category, std::string str);

	        static std::string toLoggable(const GLubyte *gluByte);

	        static std::string toLoggable(const char *chars);
        };
    }
}


#endif