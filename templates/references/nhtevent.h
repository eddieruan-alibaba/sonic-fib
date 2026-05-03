/* DO NOT EDIT -- auto-generated from schema/NhtEvent.json */
#pragma once

#include <string>
#include <cstdint>

namespace fib {

struct NhtEvent {
    std::string rnh_prefix;
    std::string prev_resolved_prefix;
    std::uint32_t prev_resolved_nhg_id = 0;
    std::string curr_resolved_prefix;
    std::uint32_t curr_resolved_nhg_id = 0;

    // Default constructor
    NhtEvent();

    // Parameterized constructor
    NhtEvent(
        const std::string& rnh_prefix_in,
        const std::string& prev_resolved_prefix_in,
        std::uint32_t prev_resolved_nhg_id_in,
        const std::string& curr_resolved_prefix_in,
        std::uint32_t curr_resolved_nhg_id_in
    );

    // Copy constructor
    NhtEvent(const NhtEvent& other);

    // Copy assignment operator
    NhtEvent& operator=(const NhtEvent& other);

    // Equality operators
    bool operator==(const NhtEvent& other) const;
    bool operator!=(const NhtEvent& other) const;

    // Destructor
    ~NhtEvent() = default;
};

} // namespace fib