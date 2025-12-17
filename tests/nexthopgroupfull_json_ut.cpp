#include <gtest/gtest.h>
#include <arpa/inet.h>

#include <iostream>
#include <thread>

#include <unistd.h>

#include "src/nexthopgroupfull.h"
#include "src/nexthopgroupfull_json.h"

using namespace std;
using namespace fib;

TEST(EnumToJson, nexthop_type)
{
    cout << "TEST_EnumToJson::nexthop_type started: " << endl;
    cout << "[DEBUG] Preparing values ..." << endl;
    /* Prepare the value */
    fib::nexthop_types_t test_val = NEXTHOP_TYPE_IPV4_IFINDEX;

    /* Call to_json function */
    cout << "[DEBUG] Calling to_json function for enum nexthop_types_t ..." << endl;
    nlohmann::json j;
    fib::to_json(j, test_val);

    /* Output the constructed JSON string */
    cout << "    [DEBUG] The constructed JSON string is:" << endl;
    cout << "    " << j.dump(4) << std::endl;
    /* Check the value of constructed JSON */
    cout << "[DEBUG] Checking JSON string values ..." << endl;
    EXPECT_EQ(j, "NEXTHOP_TYPE_IPV4_IFINDEX");

    /* Call from_json function */
    cout << "[DEBUG] Calling from_json function for enum nexthop_types_t ..." << endl;
    fib::nexthop_types_t parsed_val;
    fib::from_json(j, parsed_val);

    /* Check the value of struct parsed from JSON */
    cout << "[DEBUG] Checking STRUCT value parsed from JSON string ..." << endl;
    EXPECT_EQ(parsed_val, test_val);

    cout << "TEST_EnumToJson::nexthop_type finished." << endl;
}

TEST(EnumToJson, blackhole_type)
{
    cout << "TEST_EnumToJson::blackhole_type started: " << endl;
    /* Prepare the value */
    cout << "[DEBUG] Preparing values ..." << endl;
    fib::blackhole_type test_val = BLACKHOLE_REJECT;

    /* Call to_json function */
    cout << "[DEBUG] Calling to_json function for enum blackhole_type ..." << endl;
    nlohmann::json j;
    fib::to_json(j, test_val);

    /* Output the constructed JSON string */
    cout << "    [DEBUG] The constructed JSON string is:" << endl;
    cout << "    " << j.dump(4) << endl;
    /* Check the value of constructed JSON */
    EXPECT_EQ(j, "BLACKHOLE_REJECT");

    /* Call from_json function */
    cout << "[DEBUG] Calling from_json function for enum blackhole_type ..." << endl;
    fib::blackhole_type parsed_val;
    fib::from_json(j, parsed_val);

    /* Check the value of struct parsed from JSON */
    cout << "[DEBUG] Checking STRUCT value parsed from JSON string ..." << endl;
    EXPECT_EQ(parsed_val, test_val);

    cout << "TEST_EnumToJson::blackhole_type finished." << endl;
}

TEST(EnumToJson, lsp_type)
{
    cout << "Test_EnumToJson::lsp_type started: " << endl;
    /* Prepare the value */
    cout << "[DEBUG] Preparing values ..." << endl;
    fib::lsp_types_t test_val = ZEBRA_LSP_BGP;

    /* Call to_json function */
    cout << "[DEBUG] Calling to_json function for enum lsp_types_t ..." << endl;
    nlohmann::json j;
    fib::to_json(j, test_val);

    /* Output the constructed JSON string */
    cout << "    [DEBUG] The constructed JSON string is:" << endl;
    cout << "    " << j.dump(4) << endl;
    /* Check the value of constructed JSON */
    EXPECT_EQ(j, "ZEBRA_LSP_BGP");

    /* Call from_json function */
    cout << "[DEBUG] Calling from_json function for enum lsp_types_t ..." << endl;
    fib::lsp_types_t parsed_val;
    fib::from_json(j, parsed_val);

    /* Check the value of struct parsed from JSON */
    cout << "[DEBUG] Checking STRUCT value parsed from JSON string ..." << endl;
    EXPECT_EQ(parsed_val, test_val);

    cout << "TEST_EnumToJson::lsp_types_t finished." << endl;
}

TEST(EnumToJson, seg6local_action)
{
    cout << "Test_EnumToJson::seg6local_action started: " << endl;
    /* Prepare the value */
    cout << "[DEBUG] Preparing values ..." << endl;
    fib::seg6local_action_t test_val = SEG6_LOCAL_ACTION_END_DT46;

    /* Call to_json function */
    cout << "[DEBUG] Calling to_json function for enum seg6local_action_t ..." << endl;
    nlohmann::json j;
    fib::to_json(j, test_val);

    /* Output the constructed JSON string */
    cout << "    [DEBUG] The constructed JSON string is:" << endl;
    cout << "    " << j.dump(4) << endl;
    /* Check the value of constructed JSON */
    EXPECT_EQ(j, "SEG6_LOCAL_ACTION_END_DT46");

    /* Call from_json function */
    cout << "[DEBUG] Calling from_json function for enum seg6local_action_t ..." << endl;
    fib::seg6local_action_t parsed_val;
    fib::from_json(j, parsed_val);

    /* Check the value of struct parsed from JSON */
    cout << "[DEBUG] Checking STRUCT value parsed from JSON string ..." << endl;
    EXPECT_EQ(parsed_val, test_val);

    cout << "TEST_EnumToJson::seg6local_action_t finished." << endl;
}

TEST(EnumToJson, srv6_headend_behavior)
{
    cout << "Test_EnumToJson::srv6_headend_behavior started: " << endl;
    /* Prepare the value */
    cout << "[DEBUG] Preparing value ..." << endl;
    fib::srv6_headend_behavior test_val = SRV6_HEADEND_BEHAVIOR_H_INSERT;

    /* Call to_json function */
    cout << "[DEBUG] Calling to_json function for enum srv6_headend_behavior ..." << endl;
    nlohmann::json j;
    fib::to_json(j, test_val);

    /* Output the constructed JSON string */
    cout << "    [DEBUG] The constructed JSON string is:" << endl;
    cout << "    " << j.dump(4) << endl;
    /* Check the value of constructed JSON */
    EXPECT_EQ(j, "SRV6_HEADEND_BEHAVIOR_H_INSERT");

    /* Call from_json function */
    cout << "[DEBUG] Calling from_json function for enum sev6_headend_behavior ..." << endl;
    fib::srv6_headend_behavior parsed_val;
    fib::from_json(j, parsed_val);

    /* Check the value of struct parsed from JSON */
    cout << "[DEBUG] Checking STRUCT value parsed from JSON string ..." << endl;
    EXPECT_EQ(parsed_val, test_val);

    cout << "TEST_EnumToJson::srv6_headend_behavior finishd." << endl;
}


// --- Test: nh_grp_full ---
TEST(StructToFromJson, nh_grp_full)
{
    cout << "TEST_StructToFromJson::nh_grp_full started:" << endl;
    /* Prepare the value */
    cout << "[DEBUG] Preparing values ..." << endl;
    fib::nh_grp_full test_val{1001, 5, 3};

    /* Call to_json function */
    cout << "[DEBUG] Calling to_json for nh_grp_full ..." << endl;
    nlohmann::json j;
    fib::to_json(j, test_val);

    /* Output the constructed JSON string */
    cout << "    [DEBUG] The constructed JSON string is:" << endl;
    cout << "    " << j.dump(4) << endl;
    /* Check the values of constructed JSON */
    EXPECT_EQ(j["id"], 1001);
    EXPECT_EQ(j["weight"], 5);
    EXPECT_EQ(j["num_direct"], 3);

    /* Call from_json function */
    cout << "[DEBUG] Calling from_json for nh_grp_full ..." << endl;
    fib::nh_grp_full parsed_val;
    fib::from_json(j, parsed_val);

    /* Check the value of nh_grp_full struct parsed from JSON */
    cout << "[DEBUG] Checking STRUCT value parsed from JSON string ..." << endl;
    EXPECT_EQ(parsed_val.id, test_val.id);
    EXPECT_EQ(parsed_val.weight, test_val.weight);
    EXPECT_EQ(parsed_val.num_direct, test_val.num_direct);

    cout << "TEST_StructToFromJson::nh_grp_full finished." << endl;
}

// --- Test: seg6local_flavors_info
TEST(StructToFromJson, seg6local_flavors_info)
{
    cout << "TEST_StructToFromJson::seg6local_flavors_info started:" << endl;
    /* Prepare the value */
    cout << "[Debug] Preparing values ..." << endl;
    fib::seg6local_flavors_info test_val{1000, 32, 16};

    /* Call to_json function */
    cout << "[DEBUG] Calling to_json for seg6local_flavors_info ..." << endl;
    nlohmann::json j;
    fib::to_json(j, test_val);

    /* Output the constructed JSON string */
    cout << "    [DEBUG] The constructed JSON string is:" << endl;
    cout << "    " << j.dump(4) << endl;
    /* Check the values of constructed JSON */
    EXPECT_EQ(j["flv_ops"], test_val.flv_ops);
    EXPECT_EQ(j["lcblock_len"], test_val.lcblock_len);
    EXPECT_EQ(j["lcnode_func_len"], test_val.lcnode_func_len);

    /* Call from_json function */
    cout << "[DEBUG] Calling from_json for seg6local_flavors_info ..." << endl;
    fib::seg6local_flavors_info parsed_val;
    fib::from_json(j, parsed_val);

    /* Check the value of seg6local_flavors_info struct parsed from JSON */
    cout << "[DEBUG] Checking STRUCT value parsed from JSON string ..." << endl;
    EXPECT_EQ(parsed_val.flv_ops, test_val.flv_ops);
    EXPECT_EQ(parsed_val.lcblock_len, test_val.lcblock_len);
    EXPECT_EQ(parsed_val.lcnode_func_len, test_val.lcnode_func_len);

    cout << "TEST_StructToFromJson::seg6local_flavors_info finished." << endl;
}