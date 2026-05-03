#include <gtest/gtest.h>
#include <iostream>
#include <cstring>

#include "src/nhtevent.h"
#include "src/nhtevent_json.h"

using namespace std;
using namespace fib;

TEST(NhtEvent, default_constructor)
{
    cout << "TEST_NhtEvent::default_constructor started:" << endl;

    NhtEvent evt;
    EXPECT_EQ(evt.rnh_prefix, "");
    EXPECT_EQ(evt.prev_resolved_prefix, "");
    EXPECT_EQ(evt.prev_resolved_nhg_id, 0u);
    EXPECT_EQ(evt.curr_resolved_prefix, "");
    EXPECT_EQ(evt.curr_resolved_nhg_id, 0u);

    cout << "TEST_NhtEvent::default_constructor finished." << endl;
}

TEST(NhtEvent, parameterized_constructor)
{
    cout << "TEST_NhtEvent::parameterized_constructor started:" << endl;

    NhtEvent evt("2064:100::1d/128", "10.0.0.0/8", 266, "10.0.1.0/24", 270);

    EXPECT_EQ(evt.rnh_prefix, "2064:100::1d/128");
    EXPECT_EQ(evt.prev_resolved_prefix, "10.0.0.0/8");
    EXPECT_EQ(evt.prev_resolved_nhg_id, 266u);
    EXPECT_EQ(evt.curr_resolved_prefix, "10.0.1.0/24");
    EXPECT_EQ(evt.curr_resolved_nhg_id, 270u);

    cout << "TEST_NhtEvent::parameterized_constructor finished." << endl;
}

TEST(NhtEvent, copy_constructor)
{
    cout << "TEST_NhtEvent::copy_constructor started:" << endl;

    NhtEvent orig("2064:100::1d/128", "10.0.0.0/8", 266, "10.0.1.0/24", 270);
    NhtEvent copy(orig);

    EXPECT_EQ(copy, orig);

    cout << "TEST_NhtEvent::copy_constructor finished." << endl;
}

TEST(NhtEvent, copy_assignment)
{
    cout << "TEST_NhtEvent::copy_assignment started:" << endl;

    NhtEvent orig("2064:100::1d/128", "10.0.0.0/8", 266, "10.0.1.0/24", 270);
    NhtEvent assigned;
    assigned = orig;

    EXPECT_EQ(assigned, orig);

    cout << "TEST_NhtEvent::copy_assignment finished." << endl;
}

TEST(NhtEvent, equality_operators)
{
    cout << "TEST_NhtEvent::equality_operators started:" << endl;

    NhtEvent a("2064:100::1d/128", "10.0.0.0/8", 266, "10.0.1.0/24", 270);
    NhtEvent b("2064:100::1d/128", "10.0.0.0/8", 266, "10.0.1.0/24", 270);
    NhtEvent c("2064:100::1e/128", "10.0.0.0/8", 266, "10.0.1.0/24", 270);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a == c);

    cout << "TEST_NhtEvent::equality_operators finished." << endl;
}
