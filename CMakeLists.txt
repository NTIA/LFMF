############################################################
## CMakeList.txt : Top-level CMake project file, do global
## configuration and include sub-projects here.
############################################################

# >=3.21 required for Ninja Generators to use absolute paths.
#    See https://stackoverflow.com/questions/69846931/
#    This is relevant for specifying unit test data file paths
#    Automated testing only runs >=3.21 for this reason.
# >=3.14 required for GoogleTest v1.12.x
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# If on macOS, handle arm64/x86_64 architectures (must be done before project())
if (APPLE)
    # Get the current platform's native architecture
    execute_process(
        COMMAND uname -m
        RESULT_VARIABLE result
        OUTPUT_VARIABLE MACOS_NATIVE_ARCHITECTURE
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    message(STATUS "Current macOS architecture is " ${MACOS_NATIVE_ARCHITECTURE})

    # If running on Apple silicon, try a universal build. Otherwise, a native build.
    if ((CMAKE_GENERATOR STREQUAL "Xcode") AND (MACOS_NATIVE_ARCHITECTURE STREQUAL "arm64"))
        set(CMAKE_OSX_ARCHITECTURE "arm64;x86_64" CACHE STRING "")
        set(PROPLIB_ARCHITECTURE "macOS_universal")
        message(STATUS "Configured for universal macOS build")
    else ()
        set(PROPLIB_ARCHITECTURE MACOS_NATIVE_ARCHITECTURE)
        message(STATUS "Configured for native macOS build")
    endif ()
endif ()

###########################################
## PROJECT METADATA
###########################################
# TODO-TEMPLATE: Add project metadata here. See CREATING-REPOSITORIES.md for an example.
set(LIB_NAME "PropLibTemplate")        # Name of library/target
set(LIB_NAMESPACE "ITS")               # Namespace for the named library
project(
    "${LIB_NAMESPACE}.${LIB_NAME}"
    VERSION 1.0
    DESCRIPTION "TODO-TEMPLATE: BRIEF DESCRIPTION OF YOUR SOFTWARE"
    HOMEPAGE_URL "TODO-TEMPLATE: HOMEPAGE LINK, E.G. TO RELEVANT PAGE ON PROPLIB WIKI"
    LANGUAGES "CXX"
)

###########################################
## CMAKE OPTIONS AND DEFAULTS
###########################################
# Define options. Defaults to: compile 64-bit library and driver, build docs, run tests
option(BUILD_DOCS "Generate documentation site with Doxygen" ON)
option(BUILD_DRIVER "Build the command-line driver executable" ON)
option(RUN_DRIVER_TESTS "Test the command-line driver executable" ON)
option(DOCS_ONLY "Skip all steps except generating the documentation site" OFF)
option(RUN_TESTS "Run unit tests for the main library" ON)

###########################################
## SETUP
###########################################
# Create an interface to set common compiler flags
add_library(proplib_compiler_flags INTERFACE)

# Require at least C++11
target_compile_features(proplib_compiler_flags INTERFACE cxx_std_11)

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE generator expression
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(proplib_compiler_flags INTERFACE
    # For GCC-like compilers in any configuration
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
    # For GCC-like compilers in Release configurations
    "$<${gcc_like_cxx}:$<$<CONFIG:Release>:-O3;-DNDEBUG>>"
    # For GCC-like compilers in Debug configurations
    "$<${gcc_like_cxx}:$<$<CONFIG:Debug>:-g;-O0>>"
    # For MSVC compiler in any configuration
    "$<${msvc_cxx}:$<BUILD_INTERFACE:/W3;/Gz>>"
    # For MSVC compiler in Release configurations
    "$<${msvc_cxx}:$<$<CONFIG:Release>:/O2;/DNDEBUG>>"
    # For MSVC compiler in Debug configurations
    "$<${msvc_cxx}:$<$<CONFIG:Debug>:/Od;/Zi>>"
)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

# control where the static and shared libraries are built
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin" CACHE STRING "Set the CMAKE Archive Output Directory")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin" CACHE STRING "Set the CMAKE Library Output Directory")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin" CACHE STRING "Set the CMAKE Runtime Output Directory")

##########################################
## BUILD/RUN
##########################################
if (NOT DOCS_ONLY)
    add_subdirectory(src)  # Build the shared library
    if (RUN_TESTS OR RUN_DRIVER_TESTS)
        # Set up GoogleTest
        if (EXISTS "${PROJECT_SOURCE_DIR}/extern/googletest/CMakeLists.txt")
            enable_testing()
            set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
            # Ensure GoogleTest is built as a static library
            if (DEFINED BUILD_SHARED_LIBS AND BUILD_SHARED_LIBS)
                set(BUILD_SHARED_LIBS_${LIB_NAME} ${BUILD_SHARED_LIBS})
                set(BUILD_SHARED_LIBS OFF)
                message(STATUS "STATUS: BUILD_SHARED_LIBS is " ${BUILD_SHARED_LIBS} " to build gtest library.")
            endif ()
            add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
            include(GoogleTest)
            # Restore initial value of BUILD_SHARED_LIBS
            if (DEFINED BUILD_SHARED_LIBS_${LIB_NAME})
                set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_${LIB_NAME}})
                message(STATUS "STATUS: BUILD_SHARED_LIBS is " ${BUILD_SHARED_LIBS} " to build ${LIB_NAME} library.")
            endif ()
        else ()
            message(SEND_ERROR
                "Unable to build tests. GoogleTest submodule is missing. "
                "Run `git submodule init extern/googletest` then "
                "`git submodule update` and try again."
            )
        endif ()
    endif ()
    if (RUN_TESTS)         # Build and run unit tests
        add_subdirectory(tests)
    endif ()
    if (BUILD_DRIVER OR RUN_DRIVER_TESTS)
        add_subdirectory(app)
    endif ()
endif ()

# Generate documentation
if (BUILD_DOCS OR DOCS_ONLY)
    add_subdirectory(docs)
endif ()
