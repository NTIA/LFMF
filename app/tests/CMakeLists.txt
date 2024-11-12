############################################
## CONFIGURE COMMAND LINE DRIVER TESTS
############################################
set(DRIVER_TEST_NAME "Test${DRIVER_NAME}")

## TODO-TEMPLATE: Include source AND header files for tests here.
add_executable(
    ${DRIVER_TEST_NAME}
    "TempTextFile.cpp"
    "TestDriver.cpp"
    "TempTextFile.h"
    "TestDriver.h"
    "${DRIVER_HEADERS}/Driver.h"
)

# Add the include directories
target_include_directories(
    ${DRIVER_TEST_NAME} PUBLIC
    "${DRIVER_HEADERS}"
    "${PROJECT_SOURCE_DIR}/app/tests"
)

# Link the library to the executable
target_link_libraries(${DRIVER_TEST_NAME} ${LIB_NAME})

# Make driver executable location available to source
add_definitions(-DDRIVER_LOCATION="$<TARGET_FILE:${DRIVER_NAME}>")

set_target_properties(
    ${DRIVER_TEST_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${DRIVER_EXE_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${DRIVER_EXE_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${DRIVER_EXE_DIR}
)

###########################################
## SET UP AND DISCOVER TESTS
###########################################
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(${DRIVER_TEST_NAME} ${LIB_NAME} GTest::gtest_main)
gtest_discover_tests(${DRIVER_TEST_NAME})
