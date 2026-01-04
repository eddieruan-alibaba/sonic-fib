#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <gtest/gtest.h>
#include <arpa/inet.h>

#include <iostream>
#include <thread>

#include <unistd.h>

#include "src/c-api/nexthopgroup_capi.h"
#include "src/nexthopgroupfull.h"
#include "src/nexthopgroupfull_json.h"
#include "src/c_nexthopgroupfull.h"

using namespace std;
using namespace fib;

extern "C" {
    char* nexthopgroupfull_json_from_c_nhg_multi(const struct C_NextHopGroupFull* c_nhg, uint16_t multipaths);
    char* nexthopgroupfull_json_from_c_nhg_singleton(const struct C_NextHopGroupFull* c_nhg, uint16_t multipaths);
    void nexthopgroup_free(NextHopGroupFull* obj);
}


TEST(NextHopGroupFull_CAPI, multi_nexthop) {
    cout << "TEST_NextHopGroupFull_CAPI::multi_nexthop started: "  << endl;
    cout << "[DEBUG] Constructing values ..." << endl;

    /* Prepare the parameters */
    C_NextHopGroupFull c_nhg = {};

    c_nhg.id = 100;
    c_nhg.key = 1234567;

    // set up nh_grp_full_list
    struct nh_grp_full nh1 = {};
    nh1.id = 200;
    nh1.weight = 1;
    nh1.num_direct = 0;
    c_nhg.nh_grp_full_list[0] = nh1;

    struct nh_grp_full nh2 = {};
    nh2.id = 300;
    nh2.weight = 1;
    nh2.num_direct = 2;
    c_nhg.nh_grp_full_list[1] = nh2;

    struct nh_grp_full nh3 = {};
    nh3.id = 310;
    nh3.weight = 2;
    nh3.num_direct = 0;
    c_nhg.nh_grp_full_list[2] = nh3;

    struct nh_grp_full nh4 = {};
    nh4.id = 320;
    nh4.weight = 2;
    nh4.num_direct = 0;
    c_nhg.nh_grp_full_list[3] = nh4;

    struct nh_grp_full nh5 = {};
    nh5.id = 400;
    nh5.weight = 1;
    nh5.num_direct = 0;
    c_nhg.nh_grp_full_list[4] = nh5;

    // terminate the list with id = 0
    c_nhg.nh_grp_full_list[5].id = 0;

    // set up depends
    c_nhg.depends[0] = 200;
    c_nhg.depends[1] = 300;
    c_nhg.depends[2] = 400;
    c_nhg.depends[3] = 0;

    // set up dependents
    c_nhg.dependents[0] = 500;
    c_nhg.dependents[1] = 600;
    c_nhg.dependents[2] = 0;

    /* Call c-api to convert C_NextHopGroupFull to C++ NextHopGroupFull and return JSON string */
    cout << "[DEBUG] Calling nexthopgroupfull_json_from_c_nhg_multi ..." << endl;
    char* json_str = nexthopgroupfull_json_from_c_nhg_multi(&c_nhg, MULTIPATH_NUM);

    ASSERT_NE(json_str, nullptr) << "[ERROR] C-API returned nullptr";

    /* Output the generated JSON string */
    cout << "    [DEBUG] The generated JSON string is:" << endl;
    cout << "    " << json_str << endl;

    /* Parse JSON string and deserialize to C++ object */
    cout << "[DEBUG] Parsing JSON string and deserializing to C++ object ..." << endl;
    nlohmann::ordered_json j = nlohmann::json::parse(json_str);
    NextHopGroupFull cpp_nhg;
    from_json(j, cpp_nhg);

    /* Verify round-trip conversion by comparing C structure and C++ object */
    cout << "[DEBUG] Verifying C_NextHopGroupFull vs C++ NextHopGroupFull ..." << endl;
    // verify basic fields
    EXPECT_EQ(cpp_nhg.id, c_nhg.id);
    EXPECT_EQ(cpp_nhg.key, c_nhg.key);
    // verify nh_grp_full_list
    EXPECT_EQ(cpp_nhg.nh_grp_full_list.size(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(cpp_nhg.nh_grp_full_list[i].id, c_nhg.nh_grp_full_list[i].id);
        EXPECT_EQ(cpp_nhg.nh_grp_full_list[i].weight, c_nhg.nh_grp_full_list[i].weight);
        EXPECT_EQ(cpp_nhg.nh_grp_full_list[i].num_direct, c_nhg.nh_grp_full_list[i].num_direct);
    }
    // verify depends
    EXPECT_EQ(cpp_nhg.depends.size(), 3);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(cpp_nhg.depends[i], c_nhg.depends[i]);
    }
    // verify dependents
    EXPECT_EQ(cpp_nhg.dependents.size(), 2);
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(cpp_nhg.dependents[i], c_nhg.dependents[i]);
    }

    /* Clean up */
    free(json_str);

    cout << "TEST_NextHopGroupFull_CAPI::multi_nexthop finished." << endl;
}