###########################################
## BUILD THE LIBRARY
###########################################

message(STATUS "STATUS: Start building the libaray: " ${LIB_NAME})

# Include source AND header files here so IDEs can find them
set(LIB_HEADERS "${PROJECT_SOURCE_DIR}/include")
set(LIB_FILES
    Airy.cpp
    FlatEarthCurveCorrection.cpp
    LFMF.cpp
    ResidueSeries.cpp
    ValidateInputs.cpp
    WiRoot.cpp
    wofz.cpp
    "${LIB_HEADERS}/${PROJECT_NAME}/LFMF.h"
)

# By default, create shared library
if(NOT DEFINED BUILD_SHARED_LIBS)
    message(STATUS "STATUS: BUILD_SHARED_LIBS is not defined to build the library: " ${LIB_NAME} ".")
    add_library(${LIB_NAME} SHARED ${LIB_FILES})
else()
    message(STATUS "STATUS: BUILD_SHARED_LIBS is " ${BUILD_SHARED_LIBS} " to build the library: " ${LIB_NAME} ".")
    add_library(${LIB_NAME} ${LIB_FILES})
endif()

# Add the include directory
target_include_directories(${LIB_NAME} PUBLIC "${LIB_HEADERS}")

# Set minimum C++ version to C++11
target_compile_features(${LIB_NAME} PUBLIC cxx_std_11)

# Platform-specific configurations
if (WIN32)
    set_target_properties(${LIB_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
endif ()

# Set some target metadata
set_target_properties(
    ${LIB_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR} # Include version in .so output filenames
)

# Architecture-dependent configuration
if (BUILD_32BIT)
    set_target_properties(
        ${LIB_NAME} PROPERTIES
        DEBUG_POSTFIX "x86"
        RELEASE_POSTFIX "x86"
    )
else ()
    set_target_properties(
        ${LIB_NAME} PROPERTIES
        DEBUG_POSTFIX "x64"
        RELEASE_POSTFIX "x64"
    )
endif ()

if (DEFINED ENABLE_INSTALL AND ENABLE_INSTALL)
    # Create a variable called installable_libs that is a list of all
    # libraries we want to install (e.g. MathFunctions and tutorial_compiler_flags)
    # Then install the installable libraries to the lib folder.
    set(installable_libs ${LIB_NAME})

    install(TARGETS ${installable_libs}
            DESTINATION ${CMAKE_INSTALL_BINDIR})

    install(TARGETS ${installable_libs}
            DESTINATION ${CMAKE_INSTALL_LIBDIR})

    # Install the library headers to the include folder.
    # Hint: Use the FILES and DESTINATION parameters

    install(FILES 
            "${LIB_HEADERS}/${PROJECT_NAME}/LFMF.h" 
            DESTINATION 
            ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    )
endif()