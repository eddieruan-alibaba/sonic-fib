#pragma once

#include <functional>
#include <string>
#include <mutex>
#include <atomic>
#include <cstdint>

namespace fib {
enum class LogLevel : uint8_t {
    DEBUG = 0,
    INFO  = 1,
    WARN  = 2,
    ERROR = 3
};

// C++ interface for Define log callback function
using LogCallback = std::function<void(LogLevel level, const char* file,
                                       int line, const char* func,
                                       const std::string& msg)>;

// Register callback function
void registerLogCallback(LogCallback cb);
// Set and get log level
void setLogLevel(LogLevel level);
LogLevel getLogLevel();


// Internal logging macro (used inside library implementation)
#define FIB_LOG(level, ...) \
    do { \
        if (static_cast<int>(level) >= static_cast<int>(mylib::getLogLevel())) { \
            fib::internalLog(level, __FILE__, __LINE__, __func__, \
                               mylib::formatLog(__VA_ARGS__)); \
        } \
    } while (0)

// Internal helpers to log messages
void internalLog(LogLevel level, const char* file, int line,
                 const char* func, const std::string& msg);
std::string formatLog(const char* fmt, ...); 

} // namespace fib