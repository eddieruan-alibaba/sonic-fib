// Auto-generated from JSON Schema. DO NOT EDIT.
#pragma once

#include "nhtevent.h"
#include <nlohmann/json.hpp>
#include <string>

namespace fib {

// --- NhtEvent to_json / from_json ---
inline void to_json(nlohmann::ordered_json& j, const NhtEvent& obj) {
    j = nlohmann::ordered_json{
        {"rnh_prefix", obj.rnh_prefix},
        {"prev_resolved_prefix", obj.prev_resolved_prefix},
        {"prev_resolved_nhg_id", obj.prev_resolved_nhg_id},
        {"curr_resolved_prefix", obj.curr_resolved_prefix},
        {"curr_resolved_nhg_id", obj.curr_resolved_nhg_id},
    };
}

inline void from_json(const nlohmann::ordered_json& j, NhtEvent& obj) {
    j.at("rnh_prefix").get_to(obj.rnh_prefix);
    j.at("prev_resolved_prefix").get_to(obj.prev_resolved_prefix);
    j.at("prev_resolved_nhg_id").get_to(obj.prev_resolved_nhg_id);
    j.at("curr_resolved_prefix").get_to(obj.curr_resolved_prefix);
    j.at("curr_resolved_nhg_id").get_to(obj.curr_resolved_nhg_id);
}

// --- Top-level string helpers ---
inline std::string nhtevent_to_json_string(const NhtEvent& obj) {
    return nlohmann::ordered_json(obj).dump();
}

inline NhtEvent nhtevent_from_json_string(const std::string& json_str) {
    auto j = nlohmann::ordered_json::parse(json_str);
    return j.get<NhtEvent>();
}

} // namespace fib