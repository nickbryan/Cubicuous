#include "Logger.h"

namespace Cubicuous {
    namespace Debugging {
        void Logger::log(std::string category, std::string str) {
            std::cout << (category.empty() ? "" : "[" + category + "] ") << str << std::endl;
        }

        std::string Logger::toLoggable(unsigned const char *gluByte) {
            return std::string(gluByte, gluByte + sizeof(gluByte));
        }


    }
}