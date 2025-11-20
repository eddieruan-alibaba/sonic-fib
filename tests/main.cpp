#include "gtest/gtest.h"
#include <iostream>

using namespace std;
using namespace fib;

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment(env);
    return RUN_ALL_TESTS();
}
