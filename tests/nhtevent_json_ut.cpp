#include <gtest/gtest.h>
#include <iostream>
#include <cstring>

#include "src/nhtevent.h"
#include "src/nhtevent_json.h"
#include "src/c_nhtevent.h"
#include "src/c-api/nhtevent_capi.h"

using namespace std;
using namespace fib;

TEST(NhtEventJson, to_json_string)
{
    cout << "TEST_NhtEventJson::to_json_string started:" << endl;

    NhtEvent evt("2064:100::1d/128", "10.0.0.0/8", 266, "10.0.1.0/24", 270);

    string json_str = to_json_string(evt);
    cout << "    [DEBUG] JSON: " << json_str << endl;

    /* Parse back and verify */
    auto j = nlohmann::ordered_json::parse(json_str);
    EXPECT_EQ(j["rnh_prefix"], "2064:100::1d/128");
    EXPECT_EQ(j["prev_resolved_prefix"], "10.0.0.0/8");
    EXPECT_EQ(j["prev_resolved_nhg_id"], 266u);
    EXPECT_EQ(j["curr_resolved_prefix"], "10.0.1.0/24");
    EXPECT_EQ(j["curr_resolved_nhg_id"], 270u);

    cout << "TEST_NhtEventJson::to_json_string finished." << endl;
}

TEST(NhtEventJson, from_json)
{
    cout << "TEST_NhtEventJson::from_json started:" << endl;

    nlohmann::ordered_json j;
    j["rnh_prefix"] = "2064:100::1d/128";
    j["prev_resolved_prefix"] = "10.0.0.0/8";
    j["prev_resolved_nhg_id"] = 266;
    j["curr_resolved_prefix"] = "10.0.1.0/24";
    j["curr_resolved_nhg_id"] = 270;

    NhtEvent evt = nhtevent_from_json(j);

    EXPECT_EQ(evt.rnh_prefix, "2064:100::1d/128");
    EXPECT_EQ(evt.prev_resolved_prefix, "10.0.0.0/8");
    EXPECT_EQ(evt.prev_resolved_nhg_id, 266u);
    EXPECT_EQ(evt.curr_resolved_prefix, "10.0.1.0/24");
    EXPECT_EQ(evt.curr_resolved_nhg_id, 270u);

    cout << "TEST_NhtEventJson::from_json finished." << endl;
}

TEST(NhtEventJson, roundtrip)
{
    cout << "TEST_NhtEventJson::roundtrip started:" << endl;

    NhtEvent orig("2064:100::1d/128", "10.0.0.0/8", 266, "10.0.1.0/24", 270);

    /* Serialize -> deserialize -> compare */
    string json_str = to_json_string(orig);
    NhtEvent parsed = nhtevent_from_json_string(json_str);

    EXPECT_EQ(parsed, orig);

    cout << "TEST_NhtEventJson::roundtrip finished." << endl;
}

TEST(NhtEventJson, empty_fields)
{
    cout << "TEST_NhtEventJson::empty_fields started:" << endl;

    /* Test with empty prefix strings and zero IDs */
    NhtEvent evt("", "", 0, "", 0);

    string json_str = to_json_string(evt);
    NhtEvent parsed = nhtevent_from_json_string(json_str);

    EXPECT_EQ(parsed, evt);

    cout << "TEST_NhtEventJson::empty_fields finished." << endl;
}

TEST(NhtEventCAPI, basic)
{
    cout << "TEST_NhtEventCAPI::basic started:" << endl;

    /* Prepare a C_NhtEvent */
    C_NhtEvent c_nht = {};
    strncpy(c_nht.rnh_prefix, "2064:100::1d/128", NHT_PREFIX_MAX_LEN - 1);
    strncpy(c_nht.prev_resolved_prefix, "10.0.0.0/8", NHT_PREFIX_MAX_LEN - 1);
    c_nht.prev_resolved_nhg_id = 266;
    strncpy(c_nht.curr_resolved_prefix, "10.0.1.0/24", NHT_PREFIX_MAX_LEN - 1);
    c_nht.curr_resolved_nhg_id = 270;

    /* Call C API */
    char* json_str = nhtevent_json_from_c_nht(&c_nht);
    ASSERT_NE(json_str, nullptr) << "[ERROR] C-API returned nullptr";

    cout << "    [DEBUG] JSON: " << json_str << endl;

    /* Parse and verify */
    NhtEvent parsed = nhtevent_from_json_string(string(json_str));

    EXPECT_EQ(parsed.rnh_prefix, "2064:100::1d/128");
    EXPECT_EQ(parsed.prev_resolved_prefix, "10.0.0.0/8");
    EXPECT_EQ(parsed.prev_resolved_nhg_id, 266u);
    EXPECT_EQ(parsed.curr_resolved_prefix, "10.0.1.0/24");
    EXPECT_EQ(parsed.curr_resolved_nhg_id, 270u);

    /* Clean up */
    free(json_str);

    cout << "TEST_NhtEventCAPI::basic finished." << endl;
}

TEST(NhtEventCAPI, null_input)
{
    cout << "TEST_NhtEventCAPI::null_input started:" << endl;

    char* json_str = nhtevent_json_from_c_nht(nullptr);
    EXPECT_EQ(json_str, nullptr);

    cout << "TEST_NhtEventCAPI::null_input finished." << endl;
}
