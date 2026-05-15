// Auto-generated from JSON Schema. DO NOT EDIT.
#ifndef C_NHTEVENT_H
#define C_NHTEVENT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NHT_PREFIX_MAXLEN 64

/* --- Root Struct: C_NhtEvent --- */
struct C_NhtEvent {
    char rnh_prefix[NHT_PREFIX_MAXLEN];
    char prev_resolved_prefix[NHT_PREFIX_MAXLEN];
    uint32_t prev_resolved_nhg_id;
    char curr_resolved_prefix[NHT_PREFIX_MAXLEN];
    uint32_t curr_resolved_nhg_id;
};

#ifdef __cplusplus
}
#endif

#endif /* C_NHTEVENT_H */