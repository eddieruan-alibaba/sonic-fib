#ifndef NHTEVENT_CAPI_H
#define NHTEVENT_CAPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert NHT event fields to a JSON string.
 *
 * The caller must free() the returned string when done.
 * Returns NULL on failure.
 */
char* nhtevent_json_from_c_nht(const char* rnh_prefix,
                               const char* prev_resolved_prefix,
                               uint32_t prev_resolved_nhg_id,
                               const char* curr_resolved_prefix,
                               uint32_t curr_resolved_nhg_id);

#ifdef __cplusplus
}
#endif

#endif /* NHTEVENT_CAPI_H */
