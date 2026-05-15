#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <gtest/gtest.h>

#include "src/nhtevent.h"
#include "src/nhtevent_json.h"
#include "src/c_nhtevent.h"
#include "src/c-api/nhtevent_capi.h"

using namespace std;

/* ============ NhtEvent JSON Tests ============ */

TEST(NhtEvent_Json, to_json_basic)
{
    fib::NhtEvent evt;
    evt.rnh_prefix = "fc06::2/128";
    evt.prev_resolved_prefix = "fc06::/64";
    evt.prev_resolved_nhg_id = 237;
    evt.curr_resolved_prefix = "";
    evt.curr_resolved_nhg_id = 0;

    nlohmann::ordered_json j;
    fib::to_json(j, evt);

    EXPECT_EQ(j["rnh_prefix"], "fc06::2/128");
    EXPECT_EQ(j["prev_resolved_prefix"], "fc06::/64");
    EXPECT_EQ(j["prev_resolved_nhg_id"], 237);
    EXPECT_EQ(j["curr_resolved_prefix"], "");
    EXPECT_EQ(j["curr_resolved_nhg_id"], 0);
}

TEST(NhtEvent_Json, from_json_basic)
{
    std::string json_str = R"({
        "rnh_prefix": "10.0.0.1/32",
        "prev_resolved_prefix": "10.0.0.0/24",
        "prev_resolved_nhg_id": 100,
        "curr_resolved_prefix": "10.0.0.0/24",
        "curr_resolved_nhg_id": 200
    })";

    auto j = nlohmann::ordered_json::parse(json_str);
    fib::NhtEvent evt;
    fib::from_json(j, evt);

    EXPECT_EQ(evt.rnh_prefix, "10.0.0.1/32");
    EXPECT_EQ(evt.prev_resolved_prefix, "10.0.0.0/24");
    EXPECT_EQ(evt.prev_resolved_nhg_id, 100u);
    EXPECT_EQ(evt.curr_resolved_prefix, "10.0.0.0/24");
    EXPECT_EQ(evt.curr_resolved_nhg_id, 200u);
}

TEST(NhtEvent_Json, roundtrip)
{
    fib::NhtEvent original;
    original.rnh_prefix = "2001:db8::1/128";
    original.prev_resolved_prefix = "2001:db8::/48";
    original.prev_resolved_nhg_id = 500;
    original.curr_resolved_prefix = "";
    original.curr_resolved_nhg_id = 0;

    std::string json_str = fib::nhtevent_to_json_string(original);
    fib::NhtEvent parsed = fib::nhtevent_from_json_string(json_str);

    EXPECT_EQ(parsed.rnh_prefix, original.rnh_prefix);
    EXPECT_EQ(parsed.prev_resolved_prefix, original.prev_resolved_prefix);
    EXPECT_EQ(parsed.prev_resolved_nhg_id, original.prev_resolved_nhg_id);
    EXPECT_EQ(parsed.curr_resolved_prefix, original.curr_resolved_prefix);
    EXPECT_EQ(parsed.curr_resolved_nhg_id, original.curr_resolved_nhg_id);
}

TEST(NhtEvent_Json, nexthop_unreachable_event)
{
    /* Simulate a nexthop becoming unreachable (curr_resolved_nhg_id == 0) */
    fib::NhtEvent evt;
    evt.rnh_prefix = "fc06::2/128";
    evt.prev_resolved_prefix = "fc06::/64";
    evt.prev_resolved_nhg_id = 237;
    evt.curr_resolved_prefix = "0.0.0.0/0";
    evt.curr_resolved_nhg_id = 0;

    std::string json_str = fib::nhtevent_to_json_string(evt);
    fib::NhtEvent parsed = fib::nhtevent_from_json_string(json_str);

    EXPECT_EQ(parsed.curr_resolved_nhg_id, 0u);
    EXPECT_EQ(parsed.prev_resolved_nhg_id, 237u);
}

/* ============ NhtEvent C API Tests ============ */

TEST(NhtEvent_CAPI, basic_serialization)
{
    struct C_NhtEvent c_nht;
    memset(&c_nht, 0, sizeof(c_nht));

    strncpy(c_nht.rnh_prefix, "fc06::2/128", NHT_PREFIX_MAXLEN - 1);
    strncpy(c_nht.prev_resolved_prefix, "fc06::/64", NHT_PREFIX_MAXLEN - 1);
    c_nht.prev_resolved_nhg_id = 237;
    strncpy(c_nht.curr_resolved_prefix, "", NHT_PREFIX_MAXLEN - 1);
    c_nht.curr_resolved_nhg_id = 0;

    char* json_str = nhtevent_json_from_c_nht(&c_nht);
    ASSERT_NE(json_str, nullptr);

    /* Parse back and verify */
    fib::NhtEvent parsed = fib::nhtevent_from_json_string(json_str);
    EXPECT_EQ(parsed.rnh_prefix, "fc06::2/128");
    EXPECT_EQ(parsed.prev_resolved_prefix, "fc06::/64");
    EXPECT_EQ(parsed.prev_resolved_nhg_id, 237u);
    EXPECT_EQ(parsed.curr_resolved_prefix, "");
    EXPECT_EQ(parsed.curr_resolved_nhg_id, 0u);

    free(json_str);
}

TEST(NhtEvent_CAPI, null_input)
{
    char* json_str = nhtevent_json_from_c_nht(nullptr);
    EXPECT_EQ(json_str, nullptr);
}

TEST(NhtEvent_CAPI, ipv4_event)
{
    struct C_NhtEvent c_nht;
    memset(&c_nht, 0, sizeof(c_nht));

    strncpy(c_nht.rnh_prefix, "10.0.0.1/32", NHT_PREFIX_MAXLEN - 1);
    strncpy(c_nht.prev_resolved_prefix, "10.0.0.0/24", NHT_PREFIX_MAXLEN - 1);
    c_nht.prev_resolved_nhg_id = 42;
    strncpy(c_nht.curr_resolved_prefix, "10.0.0.0/24", NHT_PREFIX_MAXLEN - 1);
    c_nht.curr_resolved_nhg_id = 99;

    char* json_str = nhtevent_json_from_c_nht(&c_nht);
    ASSERT_NE(json_str, nullptr);

    fib::NhtEvent parsed = fib::nhtevent_from_json_string(json_str);
    EXPECT_EQ(parsed.rnh_prefix, "10.0.0.1/32");
    EXPECT_EQ(parsed.prev_resolved_nhg_id, 42u);
    EXPECT_EQ(parsed.curr_resolved_nhg_id, 99u);

    free(json_str);
}
