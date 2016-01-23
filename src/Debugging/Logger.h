#ifndef CUBICUOUS_LOGGER_H
#define CUBICUOUS_LOGGER_H

#include <array>
#include <vector>
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
            inline static void log(std::string str) { Logger::log("", str); }

            inline static void log(const char *str) { Logger::log("", str); }

            inline static void log(std::string category, const char *str) { Logger::log(category, std::string(str)); }

            static void log(std::string category, std::string str);

            inline static std::string toLoggable(const char *chars) { return std::string(chars); }



            static std::string toLoggable(const GLubyte *gluByte);

            template<typename T>
            static std::string toLoggable(const T &n) {
                //mingw32 has a bug that stops std::to_string working so implement our self
                std::ostringstream stm;
                stm << n;
                return stm.str();
            }



            template<typename T, std::size_t SIZE>
            inline static void log(std::string str, std::array<T, SIZE> arr) { Logger::log("", str, arr); }

            template<typename T>
            inline static void log(std::string str, std::vector<T> arr) { Logger::log("", str, arr); }

            template<typename T>
            inline static void log(std::string str, int size, T* arr) { Logger::log("", str, size, arr); }

            //TODO: Fix this code duplication, accept generic iterator as argument
            template<typename T>
            inline static void log(std::string category, std::string str, int size, T* arr) {
                std::string arrMsg = "";

                for(int i = 0; i < size; i++) {
                    arrMsg += Logger::toLoggable(arr[i]) + (i == size - 1 ? "" : ", ");
                }

                Logger::log(category, str + " - Size of " + Logger::toLoggable(size) + " - [" + arrMsg + "]");
            }

            template<typename T, std::size_t SIZE>
            inline static void log(std::string category, std::string str, std::array<T, SIZE> arr) {
                std::string arrMsg = "";

                for(int i = 0; i < arr.size(); i++) {
                    arrMsg += Logger::toLoggable(arr[i]) + (i == arr.size() - 1 ? "" : ", ");
                }

                Logger::log(category, str + " - Size of " + Logger::toLoggable(arr.size()) + " - [" + arrMsg + "]");
            }

            template<typename T>
            inline static void log(std::string category, std::string str, std::vector<T> arr) {
                std::string arrMsg = "";

                for(int i = 0; i < arr.size(); i++) {
                    arrMsg += Logger::toLoggable(arr[i]) + (i == arr.size() - 1 ? "" : ", ");
                }

                Logger::log(category, str + " - Size of " + Logger::toLoggable(arr.size()) + " - [" + arrMsg + "]");
            }
        };
    }
}


#endif