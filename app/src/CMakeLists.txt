###########################################
## BUILD THE DRIVER
###########################################

# configure a header file to pass the version number only
configure_file(${DRIVER_HEADERS}/DriverConfig.h.in ${DRIVER_HEADERS}/DriverConfig.h)

add_executable(
    ${DRIVER_NAME}
    "CommaSeparatedIterator.cpp"
    "Driver.cpp"
    "DriverUtils.cpp"
    "ReturnCodes.cpp"
    "LFMFModel.cpp"
    "${DRIVER_HEADERS}/CommaSeparatedIterator.h"
    "${DRIVER_HEADERS}/Driver.h"
    "${DRIVER_HEADERS}/DriverConfig.h"
    "${DRIVER_HEADERS}/ReturnCodes.h"
    "${DRIVER_HEADERS}/Structs.h"
)

# Add the include directory
target_include_directories(${DRIVER_NAME} PUBLIC "${DRIVER_HEADERS}")

# Link the library to the executable
target_link_libraries(${DRIVER_NAME} ${LIB_NAME} proplib_compiler_flags)

# Set some target metadata
set_target_properties(
    ${DRIVER_NAME} PROPERTIES
    OUTPUT_NAME ${DRIVER_NAME}-${DRIVER_VERSION}
)
