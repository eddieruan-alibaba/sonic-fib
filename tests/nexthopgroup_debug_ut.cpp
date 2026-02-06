#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <gtest/gtest.h>
#include <arpa/inet.h>

#include <iostream>
#include <thread>

#include <unistd.h>

#include "src/c-api/nexthopgroup_capi.h"
#include "src/nexthopgroup_debug.h"

using namespace std;
using fib::from_json;
using fib::to_json;



TEST(NextHopGroupDEBUG_API, register) { 
    cout << "TEST_nexthop_debug_register_api "  << endl;
    setLogLevel(fib::LogLevel::DEBUG);
    LogLevel level = getLogLevel();
    cout << "Current log level: " << static_cast<int>(level) << endl;
    registerLogCallback([](fib::LogLevel level, const char* file, int line,
                            const char* func, const char* format, va_list args) {
        const char* level_str = "DEBUG";
        switch (level) {
            case fib::LogLevel::INFO:  level_str = "INFO";  break;
            case fib::LogLevel::WARN:  level_str = "WARN";  break;
            case fib::LogLevel::ERROR: level_str = "ERROR"; break;
            default: break;
        }
        // Format the variadic arguments into a buffer
        std::array<char, 1024> buf;
        va_list args_copy;
        va_copy(args_copy, args);
        int len = vsnprintf(buf.data(), buf.size(), format, args_copy);
        va_end(args_copy);
        if (len > 0 && len < static_cast<int>(buf.size())) {
            cout << "[" << level_str << "] " << file << ":" << line << " " << func << " - " << buf.data() << endl;
        }
    });
}