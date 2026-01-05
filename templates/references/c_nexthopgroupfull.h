#ifndef C_NEXTHOPGROUPFULL_H
#define C_NEXTHOPGROUPFULL_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Manual definitions */
typedef uint32_t vrf_id_t;
typedef signed int ifindex_t;

#define MULTIPATH_NUM 256
#define MAX_NHG_RECURSION 8

union g_addr {
    struct in_addr ipv4;
    struct in6_addr ipv6;
};

/* Auto-generated Enums */
enum nexthop_types_t {
    NEXTHOP_TYPE_INVALID,
    NEXTHOP_TYPE_IFINDEX,
    NEXTHOP_TYPE_IPV4,
    NEXTHOP_TYPE_IPV4_IFINDEX,
    NEXTHOP_TYPE_IPV6,
    NEXTHOP_TYPE_IPV6_IFINDEX,
    NEXTHOP_TYPE_BLACKHOLE
};
enum lsp_types_t {
    ZEBRA_LSP_NONE,
    ZEBRA_LSP_STATIC,
    ZEBRA_LSP_LDP,
    ZEBRA_LSP_BGP,
    ZEBRA_LSP_OSPF_SR,
    ZEBRA_LSP_ISIS_SR,
    ZEBRA_LSP_SHARP,
    ZEBRA_LSP_SRTE,
    ZEBRA_LSP_EVPN
};
enum blackhole_type {
    BLACKHOLE_UNSPEC,
    BLACKHOLE_NULL,
    BLACKHOLE_REJECT,
    BLACKHOLE_ADMINPROHIB
};
enum seg6local_action_t {
    SEG6_LOCAL_ACTION_UNSPEC,
    SEG6_LOCAL_ACTION_END,
    SEG6_LOCAL_ACTION_END_X,
    SEG6_LOCAL_ACTION_END_T,
    SEG6_LOCAL_ACTION_END_DX2,
    SEG6_LOCAL_ACTION_END_DX6,
    SEG6_LOCAL_ACTION_END_DX4,
    SEG6_LOCAL_ACTION_END_DT6,
    SEG6_LOCAL_ACTION_END_DT4,
    SEG6_LOCAL_ACTION_END_B6,
    SEG6_LOCAL_ACTION_END_B6_ENCAP,
    SEG6_LOCAL_ACTION_END_BM,
    SEG6_LOCAL_ACTION_END_S,
    SEG6_LOCAL_ACTION_END_AS,
    SEG6_LOCAL_ACTION_END_AM,
    SEG6_LOCAL_ACTION_END_BPF,
    SEG6_LOCAL_ACTION_END_DT46
};
enum srv6_headend_behavior {
    SRV6_HEADEND_BEHAVIOR_H_INSERT,
    SRV6_HEADEND_BEHAVIOR_H_ENCAPS,
    SRV6_HEADEND_BEHAVIOR_H_ENCAPS_RED,
    SRV6_HEADEND_BEHAVIOR_H_ENCAPS_L2,
    SRV6_HEADEND_BEHAVIOR_H_ENCAPS_L2_RED
};

/* Auto-generated Structs */
struct nh_grp_full {
    uint32_t id;
    uint8_t weight;
    uint32_t num_direct;
};
struct seg6local_flavors_info {
    uint32_t flv_ops;
    uint8_t lcblock_len;
    uint8_t lcnode_func_len;
};
struct seg6local_context {
    struct in_addr nh4;
    struct in6_addr nh6;
    uint32_t table;
    struct seg6local_flavors_info flv;
    uint8_t block_len;
    uint8_t node_len;
    uint8_t function_len;
    uint8_t argument_len;
};

/* --- Special Struct: nexthop_srv6 --- */
struct nexthop_srv6 {
    enum seg6local_action_t seg6local_action;
    struct seg6local_context seg6local_ctx;
    struct seg6_seg_stack *seg6_segs;
};

/* --- Other C-specific structs (not in schema as objects) --- */
struct seg6_seg_stack {
    enum srv6_headend_behavior encap_behavior;
    uint8_t num_segs;
    struct in6_addr seg[0];
};

/* --- Root Struct: C_NextHopGroupFull --- */
struct C_NextHopGroupFull {
    uint32_t id;
    uint32_t key;
    uint8_t weight;
    uint8_t flags;

#define NEXTHOP_FLAG_ONLINK (1 << 3)
    struct nh_grp_full nh_grp_full_list[(MULTIPATH_NUM * MAX_NHG_RECURSION) + 1];
    uint32_t depends[MULTIPATH_NUM + 1];
    uint32_t dependents[MULTIPATH_NUM + 1];

    char _hash_begin[0];
    enum nexthop_types_t type;
    uint32_t vrf_id;
    uint32_t ifindex;
    enum lsp_types_t nh_label_type;
    union {
        union g_addr gate;
        enum blackhole_type bh_type;
    };
    union g_addr src;
    union g_addr rmap_src;
    char _hash_end[0];
    struct nexthop_srv6 *nh_srv6;
};

#ifdef __cplusplus
}
#endif

#endif /* C_NEXTHOPGROUPFULL_H */