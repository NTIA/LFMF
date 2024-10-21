############################################
## CONFIGURE UNIT TESTS
############################################
set(TEST_NAME "Test${LIB_NAME}")

# Add all unit test files here
add_executable(
    ${TEST_NAME}
    "TestLFMF.cpp"
    "LFMFGTestUtils.cpp"
    "LFMFGTest.h"
)

###########################################
## SET UP AND DISCOVER TESTS
###########################################
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
include(GoogleTest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set_target_properties(
    ${TEST_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)
target_link_libraries(${TEST_NAME} ${LIB_NAME} GTest::gtest_main)
gtest_discover_tests(${TEST_NAME})