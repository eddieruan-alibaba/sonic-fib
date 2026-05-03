#ifndef NHTEVENT_CAPI_H
#define NHTEVENT_CAPI_H

#include "src/c_nhtevent.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert a C_NhtEvent struct to a JSON string.
 *
 * The caller must free() the returned string when done.
 * Returns NULL on failure.
 */
char* nhtevent_json_from_c_nht(const struct C_NhtEvent* c_nht);

#ifdef __cplusplus
}
#endif

#endif /* NHTEVENT_CAPI_H */
