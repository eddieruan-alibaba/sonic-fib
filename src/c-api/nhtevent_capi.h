#ifndef NHTEVENT_CAPI_H
#define NHTEVENT_CAPI_H

#ifdef __cplusplus
extern "C" {
#endif

struct C_NhtEvent;

/*
 * Serialize a C_NhtEvent struct to a JSON string.
 * Returns a malloc'd string that the caller must free().
 * Returns NULL on failure.
 */
char* nhtevent_json_from_c_nht(const struct C_NhtEvent* c_nht);

#ifdef __cplusplus
}
#endif

#endif /* NHTEVENT_CAPI_H */
