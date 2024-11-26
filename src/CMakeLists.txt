###########################################
## BUILD THE LIBRARY
###########################################
## TODO-TEMPLATE: Include source AND header files here.
## TODO-TEMPLATE: See CREATING-REPOSITORIES.md for examples.
add_library(
    ${LIB_NAME} SHARED
    "ReturnCodes.cpp"
    "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}.h"
)

# Add the include directory
target_include_directories(${LIB_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Add definition to get the library name inside the library
add_definitions(-DLIBRARY_NAME="${LIB_NAME}")

# Set minimum C++ version to C++11
target_compile_features(${LIB_NAME} PUBLIC cxx_std_11)

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
)
