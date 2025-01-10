###########################################
## BUILD THE LIBRARY
###########################################
proplib_message("Configuring library ${LIB_NAME}")

message(STATUS "STATUS: Start building the libaray: " ${LIB_NAME})

# Include source AND header files here so IDEs can find them
set(LIB_HEADERS "${PROJECT_SOURCE_DIR}/include")

# configure a header file to pass the version number only
configure_file(${LIB_HEADERS}/${PROJECT_NAME}/${LIB_NAME}Config.h.in ${LIB_HEADERS}/${PROJECT_NAME}/${LIB_NAME}Config.h)

set(LIB_FILES
    Airy.cpp
    FlatEarthCurveCorrection.cpp
    LFMF.cpp
    ResidueSeries.cpp
    ReturnCodes.cpp
    ValidateInputs.cpp
    WiRoot.cpp
    wofz.cpp
    "${LIB_HEADERS}/${PROJECT_NAME}/LFMF.h"
    "${LIB_HEADERS}/${PROJECT_NAME}/${LIB_NAME}Config.h"
)

# By default, create shared library
if (NOT DEFINED BUILD_SHARED_LIBS)
    message(STATUS "STATUS: BUILD_SHARED_LIBS is not defined to build the library: " ${LIB_NAME} ".")
    add_library(${LIB_NAME} SHARED ${LIB_FILES})
else ()
    message(STATUS "STATUS: BUILD_SHARED_LIBS is " ${BUILD_SHARED_LIBS} " to build the library: " ${LIB_NAME} ".")
    add_library(${LIB_NAME} ${LIB_FILES})
endif ()

# Add the include directory
target_include_directories(${LIB_NAME} PUBLIC "${LIB_HEADERS}")

# link library to proplib_compiler_flags
# target_link_libraries(${LIB_NAME} PUBLIC proplib_compiler_flags)

# Configure compiler options
configure_proplib_target(${LIB_NAME})

# Add definition to get the library name and version inside the library
add_compile_definitions(
    LIBRARY_NAME="${LIB_NAME}"
    LIBRARY_VERSION="${PROJECT_VERSION}"
)

# Platform-specific configurations
if (WIN32)
    set_target_properties(${LIB_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
endif ()
if (UNIX)
    # avoid prefixing "lib" to the output file, for cross-platform consistency
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

# Set some target metadata
set_target_properties(
    ${LIB_NAME} PROPERTIES
    OUTPUT_NAME ${LIB_NAME}-${PROJECT_VERSION}-
    VERSION ${PROJECT_VERSION}
    DEBUG_POSTFIX ${ARCH_SUFFIX}
    RELEASE_POSTFIX ${ARCH_SUFFIX}
)

proplib_message("Done configuring library ${LIB_NAME}")