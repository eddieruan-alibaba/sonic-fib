/* DO NOT EDIT -- auto-generated from schema/NhtEvent.json */
#pragma once

#include "src/nhtevent.h"
#include <nlohmann/json.hpp>
#include <string>

namespace fib {

inline std::string to_json_string(const NhtEvent& obj) {
    nlohmann::ordered_json j;
    j["rnh_prefix"] = obj.rnh_prefix;
    j["prev_resolved_prefix"] = obj.prev_resolved_prefix;
    j["prev_resolved_nhg_id"] = obj.prev_resolved_nhg_id;
    j["curr_resolved_prefix"] = obj.curr_resolved_prefix;
    j["curr_resolved_nhg_id"] = obj.curr_resolved_nhg_id;
    return j.dump();
}

inline NhtEvent nhtevent_from_json(const nlohmann::ordered_json& j) {
    NhtEvent obj;
    obj.rnh_prefix = j.at("rnh_prefix").get<std::string>();
    obj.prev_resolved_prefix = j.at("prev_resolved_prefix").get<std::string>();
    obj.prev_resolved_nhg_id = j.at("prev_resolved_nhg_id").get<std::uint32_t>();
    obj.curr_resolved_prefix = j.at("curr_resolved_prefix").get<std::string>();
    obj.curr_resolved_nhg_id = j.at("curr_resolved_nhg_id").get<std::uint32_t>();
    return obj;
}

inline NhtEvent nhtevent_from_json_string(const std::string& json_str) {
    auto j = nlohmann::ordered_json::parse(json_str);
    return nhtevent_from_json(j);
}

} // namespace fib