#include "nexthopgroup_debug.h"
#include <cstdio>
#include <cstdarg>
#include <memory>

using namespace std;
using namespace fib;

namespace {  // ← Anonymous namespace
struct LoggerState {
    fib::LogCallback callback;
    fib::LogLevel level = fib::LogLevel::DEBUG;
    std::mutex mutex;
};

LoggerState& getState() {
    static LoggerState state;
    return state;
}

// Default fallback: print to stderr
void defaultLog(LogLevel level, const char* file, int line,
                const char* func, const std::string& msg) {
    const char* level_str = "DEBUG";
    switch (level) {
        case LogLevel::INFO:  level_str = "INFO";  break;
        case LogLevel::WARN:  level_str = "WARN";  break;
        case LogLevel::ERROR: level_str = "ERROR"; break;
        default: break;
    }
    std::fprintf(stderr, "[%s] %s:%d %s: %s\n",
                 level_str, file, line, func, msg.c_str());
}

} // anonymous namespace

void fib::registerLogCallback(LogCallback cb) {
    auto& state = getState();
    std::lock_guard<std::mutex> lock(state.mutex);
    state.callback = std::move(cb);
}

void fib::setLogLevel(LogLevel level) {
    auto& state = getState();
    std::lock_guard<std::mutex> lock(state.mutex);
    state.level = level;
}

fib::LogLevel fib::getLogLevel() {
    auto& state = getState();
    std::lock_guard<std::mutex> lock(state.mutex);
    return state.level;
}

void fib::internalLog(LogLevel level, const char* file, int line,
                        const char* func, const std::string& msg) {
    auto& state = getState();
    LogCallback cb;
    {
        std::lock_guard<std::mutex> lock(state.mutex);
        cb = state.callback ? state.callback : defaultLog;
    }
    cb(level, file, line, func, msg);
}

std::string fib::formatLog(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::vector<char> buf(256);
    int needed = std::vsnprintf(buf.data(), buf.size(), fmt, args);
    va_end(args);

    if (needed < 0) return "<format error>";
    if (static_cast<size_t>(needed) >= buf.size()) {
        buf.resize(needed + 1);
        va_start(args, fmt);
        std::vsnprintf(buf.data(), buf.size(), fmt, args);
        va_end(args);
    }
    return std::string(buf.data(), needed);
}