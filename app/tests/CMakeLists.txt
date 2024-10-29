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

# Make driver executable name and location available to source
add_definitions(-DDRIVER_NAME="${DRIVER_NAME}")
add_definitions(-DDRIVER_LOCATION="${DRIVER_EXE_DIR}/${CMAKE_BUILD_TYPE}")

set_target_properties(
    ${DRIVER_TEST_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

###########################################
## SET UP AND DISCOVER TESTS
###########################################
if (NOT ${GOOGLETEST_ADDED})
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
    include(GoogleTest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    set(GOOGLETEST_ADDED ON)
endif ()

target_link_libraries(${DRIVER_TEST_NAME} ${LIB_NAME} GTest::gtest_main)
gtest_discover_tests(${DRIVER_TEST_NAME})
