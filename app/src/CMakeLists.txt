###########################################
## BUILD THE DRIVER
###########################################
## TODO-TEMPLATE: Include source AND header files here. Do not include
## source/header files already included in `add_library()` in `src/CMakeLists.txt`
add_executable(
    ${DRIVER_NAME}
    "CommaSeparatedIterator.cpp"
    "Driver.cpp"
    "DriverUtils.cpp"
    "ReturnCodes.cpp"
    "${DRIVER_HEADERS}/CommaSeparatedIterator.h"
    "${DRIVER_HEADERS}/Driver.h"
    "${DRIVER_HEADERS}/ReturnCodes.h"
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
    OUTPUT_NAME ${DRIVER_NAME}-${DRIVER_VERSION}
    LIBRARY_OUTPUT_DIRECTORY ${DRIVER_EXE_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${DRIVER_EXE_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${DRIVER_EXE_DIR}
)

# Enable compiler warnings for common compilers
if(MSVC)
  target_compile_options(${DRIVER_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${DRIVER_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()