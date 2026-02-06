#pragma once

#include <functional>
#include <string>
#include <mutex>
#include <atomic>
#include <cstdint>

namespace fib {
enum class LogLevel : uint32_t {
    DEBUG = 0,
    INFO  = 1,
    WARN  = 2,
    ERROR = 3
};

// C++ interface for Define log callback function
using LogCallback = std::function<void(
    LogLevel level,
    const char* file,
    int line,
    const char* func,
    const char* format,  // Raw format string
    va_list args         // Raw arguments
)>;

// Register callback function
void registerLogCallback(LogCallback cb);
// Set and get log level
void setLogLevel(LogLevel level);
LogLevel getLogLevel();


// Internal logging macro (used inside library implementation)
#define FIB_LOG(level, fmt, ...) \
    do { \
        if (static_cast<int>(level) >= static_cast<int>(fib::getLogLevel())) { \
            fib::internalLog(level, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
        } \
    } while (0)

// Internal helpers to log messages
void internalLog(LogLevel level, const char* file, int line,
                 const char* func, const char* format, ...);


} // namespace fib