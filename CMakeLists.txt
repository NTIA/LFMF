# >=3.21 required for Ninja Generators to use absolute paths.
#    See https://stackoverflow.com/questions/69846931/
#    This is relevant for specifying unit test data file paths
#    Automated testing only runs >=3.21 for this reason.
# >=3.14 required for GoogleTest v1.12.x
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

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
# GoogleTest v1.12.1 requires at least C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##########################################
## BUILD/RUN
##########################################
if (NOT DOCS_ONLY)
    add_subdirectory(src)  # Build the shared library
    if (RUN_TESTS OR RUN_DRIVER_TESTS)
        if (EXISTS "${PROJECT_SOURCE_DIR}/extern/googletest/CMakeLists.txt")
            enable_testing()
            set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
            add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
            include(GoogleTest)
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
