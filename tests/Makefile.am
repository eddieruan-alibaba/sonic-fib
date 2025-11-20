bin_PROGRAMS += tests/tests

CFLAGS_GTEST =
LDADD_GTEST = -L/usr/src/gtest -lgtest -lgtest_main -lgmock -lgmock_main

tests_tests_SOURCES = tests/c_api_ut.cpp                \
                      tests/nexthopgroupfull_ut.cpp     \
                      tests/main.cpp

tests_tests_CFLAGS = $(DBGFLAGS) $(AM_CFLAGS) $(CFLAGS_COMMON) $(CFLAGS_GTEST)
tests_tests_CPPFLAGS = $(DBGFLAGS) $(AM_CFLAGS) $(CFLAGS_COMMON) $(CFLAGS_GTEST)  -fno-access-control
tests_tests_LDADD = $(LDADD_GTEST) -lpthread  src/libnexthopgroup.la $(CODE_COVERAGE_LIBS) -lzmq -luuid -lboost_serialization

