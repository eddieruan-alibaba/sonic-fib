// Auto-generated from JSON Schema. DO NOT EDIT.
#pragma once

#include <string>
#include <cstdint>

namespace fib {

    /* --- Struct: NhtEvent --- */
    struct NhtEvent {
        std::string rnh_prefix = "";
        std::string prev_resolved_prefix = "";
        std::uint32_t prev_resolved_nhg_id = 0;
        std::string curr_resolved_prefix = "";
        std::uint32_t curr_resolved_nhg_id = 0;
    };

} // namespace fib