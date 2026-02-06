// nexthopgroup_capi.cpp

#include "src/nexthopgroupfull.h"
#include "src/nexthopgroupfull_json.h"
#include "src/c_nexthopgroupfull.h"
#include "src/nexthopgroup_debug.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;


// Optional: bring into global scope for convenience
using NextHopGroupFull = fib::NextHopGroupFull;

// Declare C-compatible API directly (no need for header here)
extern "C" {

char* nexthopgroupfull_json_from_c_nhg_multi(const struct C_NextHopGroupFull* c_nhg, uint16_t multipaths);
char* nexthopgroupfull_json_from_c_nhg_singleton(const struct C_NextHopGroupFull* c_nhg, uint16_t multipaths);
void nexthopgroup_free(NextHopGroupFull* obj);
char* nexthopgroup_to_json(NextHopGroupFull* obj);

char* nexthopgroupfull_json_from_c_nhg_multi(const struct C_NextHopGroupFull* c_nhg, uint16_t multipaths)
{
    if (!c_nhg) {
        cout << "[CPP DEBUG] Do NOT pass in an empty C_NextHopGroupFull *" << endl;
        return nullptr;
    }

    try {
        cout << "[CPP DEBUG] nexthopgroupfull_json_from_c_nhg_multi::Converting C_NextHopGroupFull to NextHopGroupFull started ..." << endl;

        /* Convert C array to C++ vector */
        cout << "[CPP DEBUG] Converting C nh_grp_full[] to C++ vector ..." << endl;
        vector<fib::nh_grp_full> cpp_nh_grp_full_list;
        for (int i = 0; i < (MULTIPATH_NUM * MAX_NHG_RECURSION) + 1; i++) {
            if (c_nhg->nh_grp_full_list[i].id == 0) {
                break;
            }
            /* convert C nh_grp_full to C++ fib::nh_grp_full explicitly */
            fib::nh_grp_full cpp_nh = {
                c_nhg->nh_grp_full_list[i].id,
                c_nhg->nh_grp_full_list[i].weight,
                c_nhg->nh_grp_full_list[i].num_direct
            };
            cpp_nh_grp_full_list.push_back(cpp_nh);
        }
        cout << "[CPP DEBUG] Converting C depends[] to C++ vector ..." << endl;
        vector<uint32_t> cpp_depends;
        for (int i = 0; i < MULTIPATH_NUM + 1; i++) {
            if (c_nhg->depends[i] == 0) {
                break;
            }
            cpp_depends.push_back(c_nhg->depends[i]);
        }
        cout << "[CPP DEBUG] Converting C dependents[] to C++ vector ..." << endl;
        vector<uint32_t> cpp_dependents;
        for (int i = 0; i < MULTIPATH_NUM + 1; i++) {
            if (c_nhg->dependents[i] == 0) {
                break;
            }
            cpp_dependents.push_back(c_nhg->dependents[i]);
        }

        /* Call NextHopGroupFull constructor(multi) to create NextHopGroupFull object */
        NextHopGroupFull* cpp_nhg = new NextHopGroupFull(c_nhg->id, c_nhg->key,
                                                                cpp_nh_grp_full_list,
                                                                cpp_depends, cpp_dependents);

        cout << "[CPP DEBUG] nexthopgroupfull_json_from_c_nhg_multi::Converting C Obj to C++ Obj finished." << endl;

        /* Convert C++ Obj to JSON stirng */
        cout << "[CPP DEBUG] nexthopgroupfull_json_from_c_nhg_multi::Converting C++ Obj to JSON string started ..." << endl;
        char* json_str = nexthopgroup_to_json(cpp_nhg);
        cout << "[CPP DEBUG] nexthopgroupfull_json_from_c_nhg_multi::Converting C++ Obj to JSON string finished." << endl;

        nexthopgroup_free(cpp_nhg);

        return json_str;

    } catch (...) {
        cout << "[CPP ERROR] nexthopgroupfull_json_from_c_nhg_multi::Converting failed" << endl;
        return nullptr;
    }
}

char* nexthopgroupfull_json_from_c_nhg_singleton(const struct C_NextHopGroupFull* c_nhg, uint16_t multipaths)
{
    if (!c_nhg) {
        cout << "[CPP DEBUG] Do NOT pass in an empty C_NextHopGroupFull *" << endl;
        return nullptr;
    }

    try {
        cout << "[CPP DEBUG] nexthopgroupfull_json_from_c_nhg_singleton::Converting C_NextHopGroupFull to NextHopGroupFull started:" << endl;

        /* Convert C array to C++ vector */
        cout << "[CPP DEBUG] Converting C depends[] to C++ vector ..." << endl;
        vector<uint32_t> cpp_depends;
        for (int i = 0; i < MULTIPATH_NUM + 1; i++) {
            if (c_nhg->depends[i] == 0) {
                break;
            }
            cpp_depends.push_back(c_nhg->depends[i]);
        }
        cout << "[CPP DEBUG] Converting C dependents[] to C++ vector ..." << endl;
        vector<uint32_t> cpp_dependents;
        for (int i = 0; i < MULTIPATH_NUM + 1; i++) {
            if (c_nhg->dependents[i] == 0) {
                break;
            }
            cpp_dependents.push_back(c_nhg->dependents[i]);
        }

        /* Almostly we do NOT have ifname in zebra, so set it as empty string */
        std::string cpp_ifname = "";

        /* Convert seg6_segs flexible array to C++ vector */
        cout << "[CPP DEBUG] Converting seg6_segs flexible array to C++ vector ..." << endl;
        vector<struct in6_addr> cpp_nh_segs;
        if (c_nhg->nh_srv6 && c_nhg->nh_srv6->seg6_segs) {
            for (uint8_t i = 0; i < c_nhg->nh_srv6->seg6_segs->num_segs; i++) {
                cpp_nh_segs.push_back(c_nhg->nh_srv6->seg6_segs->seg[i]);
            }
        }

        /* Convert g_addr from C type to C++ type */
        fib::g_addr cpp_gate = reinterpret_cast<const fib::g_addr&>(c_nhg->gate);
        fib::g_addr cpp_src = reinterpret_cast<const fib::g_addr&>(c_nhg->src);
        fib::g_addr cpp_rmap_src = reinterpret_cast<const fib::g_addr&>(c_nhg->rmap_src);

        /* Call NextHopGroupFull constructor(singleton) to create NextHopGroupFull object */
        /* Convert C types to C++ fib types by force */
        NextHopGroupFull* cpp_nhg = new NextHopGroupFull(c_nhg->id, c_nhg->key,
                                                         static_cast<fib::nexthop_types_t>(c_nhg->type),
                                                         static_cast<fib::vrf_id_t>(c_nhg->vrf_id),
                                                         static_cast<fib::ifindex_t>(c_nhg->ifindex),
                                                         cpp_ifname, cpp_depends, cpp_dependents,
                                                         static_cast<fib::lsp_types_t>(c_nhg->nh_label_type),
                                                         static_cast<fib::blackhole_type>(c_nhg->bh_type),
                                                         cpp_gate,
                                                         cpp_src, cpp_rmap_src,c_nhg->weight, c_nhg->flags,
                                                         c_nhg->nh_srv6 != nullptr,
                                                         c_nhg->nh_srv6 && c_nhg->nh_srv6->seg6_segs != nullptr,
                                                         reinterpret_cast<const fib::nexthop_srv6*>(c_nhg->nh_srv6),
                                                         reinterpret_cast<const fib::seg6_seg_stack*>(c_nhg->nh_srv6 ? c_nhg->nh_srv6->seg6_segs : nullptr),
                                                         cpp_nh_segs);

        cout << "[CPP DEBUG] nexthopgroupfull_json_from_c_nhg_singleton::Converting C Obj to C++ Obj finished." << endl;

        /* Convert C++ Obj to JSON string */
        cout << "[CPP DEBUG] nexthopgroupfull_json_from_c_nhg_singleton::Converting C++ Obj to JSON string started ..." << endl;
        char* json_str = nexthopgroup_to_json(cpp_nhg); 
        cout << "[CPP DEBUG] nexthopgroupfull_json_from_c_nhg_singleton::Converting C++ Obj to JSON string finished." << endl;

        nexthopgroup_free(cpp_nhg);

        return json_str;

    } catch (...) {
        cout << "[CPP ERROR] nexthopgroupfull_json_from_c_nhg_singleton::Converting failed" << endl;
        return nullptr;
    }
}

void nexthopgroup_free(NextHopGroupFull* obj)
{
    delete obj;
}

char* nexthopgroup_to_json(NextHopGroupFull* obj)
{
    if (!obj) {
        return nullptr;
    }

    try {
        std::string json_str = to_json_string(*obj);
        char* c_str = static_cast<char*>(std::malloc(json_str.size() + 1));
        if (c_str) {
            std::memcpy(c_str, json_str.c_str(), json_str.size() + 1);
        }
        return c_str;
    } catch (...) {
        return nullptr;
    }
}

// Global C callback pointer (set by FRR)
/* C callback signature matching FRR's needs */
typedef void (*fib_frr_log_fn)(int level,
                                const char *file,
                                int line,
                                const char *func,
                                const char *fmt,
                                va_list args);

static fib_frr_log_fn g_frr_cb = nullptr;

// C++ wrapper that forwards to C callback
static void frr_cpp_callback(fib::LogLevel level,
                             const char* file,
                             int line,
                             const char* func,
                             const char* format,
                             va_list args) {
    if (!g_frr_cb) return;

    // Forward directly to C callback (no copying needed – va_list is consumed once)
    g_frr_cb(static_cast<int>(level), file, line, func, format, args);
}
void fib_frr_register_callback(fib_frr_log_fn cb) {
    g_frr_cb = cb;
    if (cb) {
        // Bridge C callback → C++ API
        fib::registerLogCallback(frr_cpp_callback);
    } else {
        fib::registerLogCallback(nullptr);
    }
}

void fib_frr_set_log_level(int level) {
    // Map (0-3) to fib::LogLevel
    if (level >= 0 && level <= 3) {
        fib::setLogLevel(static_cast<fib::LogLevel>(level));
    }
}

} // extern "C"