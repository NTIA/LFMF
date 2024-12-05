############################################
## CONFIGURE UNIT TESTS
############################################
set(TEST_NAME "Test${LIB_NAME}")

## TODO-TEMPLATE: Include all source AND header files for tests here.
## Do not include the source and header files of the library under test.
add_executable(
    ${TEST_NAME}
    "TestUtils.cpp"
    "TestUtils.h"
)

###########################################
## SET UP AND DISCOVER TESTS
###########################################
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(${TEST_NAME} ${LIB_NAME} GTest::gtest_main)
gtest_discover_tests(${TEST_NAME})