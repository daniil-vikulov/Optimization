#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <vector>
#include <iostream>

class Logger {
public:
    ///@brief info logging
    template<typename... Args>
    static void info(const char *filePath, Args... args) {
        std::cout << parseFileName("[INFO]", filePath);
        ((std::cout << args << ' '), ...) << '\n';
    }

    ///@brief fatal logging with immediate termination
    template<typename... Args>
    static void fatal(const char *filePath, Args... args) {
        std::cout << parseFileName("[FATAL]", filePath);
        ((std::cout << args << ' '), ...) << std::endl;

        abort();
    }

    ///@brief error logging. Does not terminate the program
    template<typename... Args>
    static void error(const char *filePath, Args... args) {
        std::cout << parseFileName("[ERROR]", filePath);
        ((std::cout << args << ' '), ...) << '\n';
    }

    ///@brief waring logging
    template<typename... Args>
    static void warning(const char *filePath, Args... args) {
        std::cout << parseFileName("[WARNING]", filePath);
        ((std::cout << args << ' '), ...) << '\n';
    }

private:
    ///@brief extracts fileName and format it for logging
    static std::string parseFileName(const char *logType, const char *filePath);
};


#define logI(...) Logger::info(__FILE__, __VA_ARGS__)
#define logF(...) Logger::fatal(__FILE__, __VA_ARGS__)
#define logE(...) Logger::error(__FILE__, __VA_ARGS__)
#define logW(...) Logger::warning(__FILE__, __VA_ARGS__)

#endif