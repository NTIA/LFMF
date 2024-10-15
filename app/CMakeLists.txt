###########################################
## BUILD THE DRIVER
###########################################
set(DRIVER_NAME "${LIB_NAME}Driver")
set(DRIVER_VERSION ${PROJECT_VERSION}) # May be set manually instead
## TODO-TEMPLATE: Include source AND header files here. Do not include
## source/header files already included in `add_library()` in `src/CMakeLists.txt`
add_executable(
    ${DRIVER_NAME}
    "main.cpp"
    "Driver.h"
    "Errors.h"
    "Structs.h"
    "Utils.cpp"
)

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

# Architecture-dependent configuration
if (BUILD_32BIT)
    set_target_properties(
        ${DRIVER_NAME} PROPERTIES
        DEBUG_POSTFIX "x86"
        RELEASE_POSTFIX "x86"
    )
else ()
    set_target_properties(
        ${DRIVER_NAME} PROPERTIES
        DEBUG_POSTFIX "x64"
        RELEASE_POSTFIX "x64"
    )
endif ()

# Build and run driver tests
if (RUN_DRIVER_TESTS)
    add_subdirectory(tests)
endif()
