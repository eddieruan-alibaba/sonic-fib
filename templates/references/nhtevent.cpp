/* DO NOT EDIT -- auto-generated from schema/NhtEvent.json */
#include "src/nhtevent.h"

namespace fib {

// Default constructor
NhtEvent::NhtEvent()
    : rnh_prefix("")
    , prev_resolved_prefix("")
    , prev_resolved_nhg_id(0)
    , curr_resolved_prefix("")
    , curr_resolved_nhg_id(0)
{
}

// Parameterized constructor
NhtEvent::NhtEvent(
    const std::string& rnh_prefix_in,
    const std::string& prev_resolved_prefix_in,
    std::uint32_t prev_resolved_nhg_id_in,
    const std::string& curr_resolved_prefix_in,
    std::uint32_t curr_resolved_nhg_id_in
)
    : rnh_prefix(rnh_prefix_in)
    , prev_resolved_prefix(prev_resolved_prefix_in)
    , prev_resolved_nhg_id(prev_resolved_nhg_id_in)
    , curr_resolved_prefix(curr_resolved_prefix_in)
    , curr_resolved_nhg_id(curr_resolved_nhg_id_in)
{
}

// Copy constructor
NhtEvent::NhtEvent(const NhtEvent& other)
    : rnh_prefix(other.rnh_prefix)
    , prev_resolved_prefix(other.prev_resolved_prefix)
    , prev_resolved_nhg_id(other.prev_resolved_nhg_id)
    , curr_resolved_prefix(other.curr_resolved_prefix)
    , curr_resolved_nhg_id(other.curr_resolved_nhg_id)
{
}

// Copy assignment operator
NhtEvent& NhtEvent::operator=(const NhtEvent& other)
{
    if (this != &other) {
        rnh_prefix = other.rnh_prefix;
        prev_resolved_prefix = other.prev_resolved_prefix;
        prev_resolved_nhg_id = other.prev_resolved_nhg_id;
        curr_resolved_prefix = other.curr_resolved_prefix;
        curr_resolved_nhg_id = other.curr_resolved_nhg_id;
    }
    return *this;
}

// Equality operator
bool NhtEvent::operator==(const NhtEvent& other) const
{
    return rnh_prefix == other.rnh_prefix &&
           prev_resolved_prefix == other.prev_resolved_prefix &&
           prev_resolved_nhg_id == other.prev_resolved_nhg_id &&
           curr_resolved_prefix == other.curr_resolved_prefix &&
           curr_resolved_nhg_id == other.curr_resolved_nhg_id;
}

bool NhtEvent::operator!=(const NhtEvent& other) const
{
    return !(*this == other);
}

} // namespace fib