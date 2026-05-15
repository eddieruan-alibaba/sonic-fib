// nhtevent_capi.cpp
// C API bridge: converts C_NhtEvent to JSON string via C++ NhtEvent

#include "src/nhtevent.h"
#include "src/nhtevent_json.h"
#include "src/c_nhtevent.h"
#include "src/nexthopgroup_debug.h"
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {

char* nhtevent_json_from_c_nht(const struct C_NhtEvent* c_nht)
{
    if (!c_nht) {
        FIB_LOG(fib::LogLevel::ERROR, "nhtevent_json_from_c_nht: NULL c_nht pointer");
        return nullptr;
    }

    try {
        fib::NhtEvent evt;
        evt.rnh_prefix = c_nht->rnh_prefix;
        evt.prev_resolved_prefix = c_nht->prev_resolved_prefix;
        evt.prev_resolved_nhg_id = c_nht->prev_resolved_nhg_id;
        evt.curr_resolved_prefix = c_nht->curr_resolved_prefix;
        evt.curr_resolved_nhg_id = c_nht->curr_resolved_nhg_id;

        std::string json_str = fib::nhtevent_to_json_string(evt);

        FIB_LOG(fib::LogLevel::DEBUG, "nhtevent json_str length %zu, str: %s",
                json_str.size(), json_str.c_str());

        char* result = static_cast<char*>(malloc(json_str.size() + 1));
        if (!result) {
            FIB_LOG(fib::LogLevel::ERROR, "nhtevent_json_from_c_nht: malloc failed");
            return nullptr;
        }
        memcpy(result, json_str.c_str(), json_str.size() + 1);
        return result;

    } catch (...) {
        FIB_LOG(fib::LogLevel::ERROR, "nhtevent_json_from_c_nht: serialization exception");
        return nullptr;
    }
}

} // extern "C"
