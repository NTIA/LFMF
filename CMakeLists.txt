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
set(LIB_NAME "TODO-TEMPLATE: YOUR-LIBRARY")             # Name of library/target
set(LIB_NAMESPACE "TODO-TEMPLATE: ITS.YOUR-NAMESPACE")  # Namespace for the named library
project(
    "${LIB_NAMESPACE}.${LIB_NAME}"
    VERSION 1.0.0
    DESCRIPTION "TODO-TEMPLATE: BRIEF DESCRIPTION OF YOUR SOFTWARE"
    HOMEPAGE_URL "TODO-TEMPLATE: HOMEPAGE LINK, E.G. TO RELEVANT PAGE ON PROPLIB WIKI"
    LANGUAGES "CXX"
)

###########################################
## SPECIFY MULTI-LANGUAGE WRAPPERS
###########################################
set(DOTNET_WRAPPER_DIR "${PROJECT_SOURCE_DIR}/wrap/dotnet")
set(MATLAB_WRAPPER_DIR "${PROJECT_SOURCE_DIR}/wrap/matlab")
set(PYTHON_WRAPPER_DIR "${PROJECT_SOURCE_DIR}/wrap/python")

###########################################
## CMAKE OPTIONS AND DEFAULTS
###########################################
# Define options. Defaults to: compile 64-bit library and driver, build docs, run tests
option(BUILD_DOCS "Generate documentation with Doxygen" ON)
option(BUILD_DRIVER "Build driver executable" ON)
option(RUN_DRIVER_TESTS "Test the driver executable" ON)
option(DOCS_ONLY "Skip all steps except generating documentation" OFF)
option(RUN_TESTS "Run C++ unit tests with Google Test + CTest" ON)
option(COPY_TO_WRAPPERS "Copy compiled library into wrapper submodules" ON)

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
    if (COPY_TO_WRAPPERS)  # Copy compiled library to wrappers
        add_subdirectory(wrap)
    endif ()
    if (RUN_TESTS)         # Build and run unit tests
        if (EXISTS "${PROJECT_SOURCE_DIR}/extern/googletest/CMakeLists.txt")
            enable_testing()
            add_subdirectory(tests)
        else ()
            message(SEND_ERROR
                "Unable to build tests. GoogleTest submodule is missing. "
                "Run `git submodule init extern/googletest` then "
                "`git submodule update` and try again."
            )
        endif()
    endif ()
    if (BUILD_DRIVER)
        add_subdirectory(app)
    endif ()
endif ()

# Generate documentation
if (BUILD_DOCS OR DOCS_ONLY)
    add_subdirectory(docs)
endif ()
