// nhtevent_capi.cpp
// C API bridge: converts C_NhtEvent to JSON string via C++ NhtEvent

#include "src/nhtevent.h"
#include "src/nhtevent_json.h"
#include "src/c_nhtevent.h"
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {

char* nhtevent_json_from_c_nht(const struct C_NhtEvent* c_nht)
{
    if (!c_nht) {
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

        char* result = static_cast<char*>(malloc(json_str.size() + 1));
        if (!result) {
            return nullptr;
        }
        memcpy(result, json_str.c_str(), json_str.size() + 1);
        return result;

    } catch (...) {
        return nullptr;
    }
}

} // extern "C"
