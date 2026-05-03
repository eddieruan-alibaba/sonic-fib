/* DO NOT EDIT -- auto-generated from schema/NhtEvent.json */
#ifndef C_NHTEVENT_H
#define C_NHTEVENT_H

#include <stdint.h>

#define NHT_PREFIX_MAX_LEN 64

struct C_NhtEvent {
    char rnh_prefix[NHT_PREFIX_MAX_LEN];
    char prev_resolved_prefix[NHT_PREFIX_MAX_LEN];
    uint32_t prev_resolved_nhg_id;
    char curr_resolved_prefix[NHT_PREFIX_MAX_LEN];
    uint32_t curr_resolved_nhg_id;
};

#endif /* C_NHTEVENT_H */