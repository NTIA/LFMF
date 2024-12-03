###########################################
## BUILD THE LIBRARY
###########################################
message(STATUS "STATUS: Start building the library: " ${LIB_NAME})

set(LIB_HEADERS "${PROJECT_SOURCE_DIR}/include")
set(LIB_FILES
    "ReturnCodes.cpp"
    "${LIB_HEADERS}/${LIB_NAME}.h"
    ## TODO-TEMPLATE: Include source AND header files here.
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
target_link_libraries(${LIB_NAME} PUBLIC proplib_compiler_flags)

# Add definition to get the library name inside the library
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
    OUTPUT_NAME ${LIB_NAME}-${PROJECT_VERSION}
    VERSION ${PROJECT_VERSION}
)
