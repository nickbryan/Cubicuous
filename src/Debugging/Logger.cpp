#include "Logger.h"

namespace Cubicuous {
    namespace Debugging {
        void Logger::log(std::string str) {
            Logger::log("", str);
        }

        void Logger::log(const char *str) {
            Logger::log("", str);
        }

        void Logger::log(const char *category, const char *str) {
            Logger::log(std::string(category), std::string(str));
        }

        void Logger::log(std::string category, std::string str) {
            std::cout << (category.empty() ? "" : "[" + category + "] ") << str << std::endl;
        }

        std::string Logger::toLoggable(unsigned const char *gluByte) {
            return std::string(gluByte, gluByte + sizeof(gluByte));
        }

        std::string Logger::toLoggable(const char *chars) {
            return std::string(chars);
        }
    }
}