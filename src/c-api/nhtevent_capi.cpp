// nhtevent_capi.cpp

#include "src/nhtevent.h"
#include "src/nhtevent_json.h"
#include "src/c_nhtevent.h"
#include "src/nexthopgroup_debug.h"
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;
using NhtEvent = fib::NhtEvent;

extern "C" {

char* nhtevent_json_from_c_nht(const struct C_NhtEvent* c_nht)
{
    if (!c_nht) {
        FIB_LOG(fib::LogLevel::ERROR, "Do NOT pass in an empty C_NhtEvent *");
        return nullptr;
    }

    try {
        /* Convert C_NhtEvent to C++ NhtEvent */
        NhtEvent cpp_nht(
            std::string(c_nht->rnh_prefix),
            std::string(c_nht->prev_resolved_prefix),
            c_nht->prev_resolved_nhg_id,
            std::string(c_nht->curr_resolved_prefix),
            c_nht->curr_resolved_nhg_id
        );

        /* Serialize to JSON string */
        std::string json_str = fib::to_json_string(cpp_nht);

        FIB_LOG(fib::LogLevel::DEBUG, "nhtevent json_str length %zu, str: %s",
            json_str.size(), json_str.c_str());

        /* Return a malloc'd copy for C caller to free() */
        char* c_str = static_cast<char*>(std::malloc(json_str.size() + 1));
        if (c_str) {
            std::memcpy(c_str, json_str.c_str(), json_str.size() + 1);
        }
        return c_str;

    } catch (...) {
        FIB_LOG(fib::LogLevel::ERROR, "nhtevent_json_from_c_nht::Converting failed");
        return nullptr;
    }
}

} // extern "C"
