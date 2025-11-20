#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <vector>


#include "src/c-api/nexthopgroup_capi.h"
#include "gtest/gtest.h"

TEST(c_api, NexthopGroupFull_CAPI) {
    NextHopGroupFull *nexthop_obj_ptr  = nexthopgroup_create();
    char *ret_str = nexthopgroup_to_json(nexthop_obj_ptr);

    printf("Convert NextHopGroupFull to string: %s\n", ret_str);

    free(ret_str);
    nexthopgroup_free(nexthop_obj_ptr);
}
