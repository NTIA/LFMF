############################################
## CONFIGURE UNIT TESTS
############################################
set(TEST_NAME "${LIB_NAME}GTest")

message(STATUS "STATUS: Start building the google tests: " ${TEST_NAME})

# Add all google test files here
add_executable(
    ${TEST_NAME}
    "TestLFMFReturnCode.cpp"
    "TestLFMFEquivalent.cpp"
    "LFMFGTestUtils.cpp"
    "LFMFGTest.h"
)

###########################################
## SET UP AND DISCOVER TESTS
###########################################

target_compile_features(${TEST_NAME} PUBLIC cxx_std_17)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(${TEST_NAME} ${LIB_NAME} GTest::gtest_main)
gtest_discover_tests(${TEST_NAME})
