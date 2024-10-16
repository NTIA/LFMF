###########################################
## BUILD THE DRIVER
###########################################
set(DRIVER_NAME "${LIB_NAME}Driver")
set(DRIVER_VERSION ${PROJECT_VERSION}) # May be set manually instead
set(DRIVER_HEADERS "${PROJECT_SOURCE_DIR}/app/include")
## TODO-TEMPLATE: Include source AND header files here. Do not include
## source/header files already included in `add_library()` in `src/CMakeLists.txt`
add_executable(
    ${DRIVER_NAME}
    "CommaSeparatedIterator.cpp"
    "Driver.cpp"
    "DriverUtils.cpp"
    "${DRIVER_HEADERS}/Driver.h"
    "${DRIVER_HEADERS}/Errors.h"
    "${DRIVER_HEADERS}/Structs.h"
)

# Add the include directory
target_include_directories(${DRIVER_NAME} PUBLIC "${DRIVER_HEADERS}")

# Link the library to the executable
target_link_libraries(${DRIVER_NAME} ${LIB_NAME})

# Add definitions to enable version identification inside the driver
add_definitions(-DLIBRARY_VERSION="${PROJECT_VERSION}")
add_definitions(-DDRIVER_VERSION="${DRIVER_VERSION}")
add_definitions(-DLIBRARY_NAME="${LIB_NAME}")
add_definitions(-DDRIVER_NAME="${DRIVER_NAME}")

# Set some target metadata
set_target_properties(
    ${DRIVER_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR} # Include version in .so output filenames
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)
