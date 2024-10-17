############################################
## CONFIGURE COMMAND LINE DRIVER TESTS
############################################
set(DRIVER_TEST_NAME "Test${DRIVER_NAME}")

## TODO-TEMPLATE: Include source AND header files for tests here.
add_executable(
    ${DRIVER_TEST_NAME}
    "TestDriver.cpp"
    "TestDriverUtils.cpp"
    "TestDriver.h"
    "${DRIVER_HEADERS}/Driver.h"
)

# Add the include directory
target_include_directories(
    ${DRIVER_TEST_NAME} PUBLIC
    "${DRIVER_HEADERS}"
    "${PROJECT_SOURCE_DIR}/app/tests"
)

# Link the library to the executable
target_link_libraries(${DRIVER_TEST_NAME} ${LIB_NAME})

# Make driver executable name available to source
add_definitions(-DDRIVER_NAME="${DRIVER_NAME}")

set_target_properties(
    ${DRIVER_TEST_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)
