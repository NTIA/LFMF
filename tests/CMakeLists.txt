############################################
## CONFIGURE UNIT TESTS
############################################
set(TEST_NAME "Test${LIB_NAME}")

message(STATUS "STATUS: Start building the google tests: " ${TEST_NAME})

# Add all unit test files here
add_executable(
    ${TEST_NAME}
    "TestLFMF.cpp"
    "LFMFGTestUtils.cpp"
    "LFMFGTest.h"
)

###########################################
## SET UP AND DISCOVER TESTS
###########################################
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
if (DEFINED BUILD_SHARED_LIBS AND BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
    option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
    message(STATUS "STATUS: BUILD_SHARED_LIBS is " ${BUILD_SHARED_LIBS} " to build gtest library.")
endif()
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/googletest" "extern/googletest")
include(GoogleTest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_compile_features(${TEST_NAME} PUBLIC cxx_std_17)
target_link_libraries(${TEST_NAME} ${LIB_NAME} GTest::gtest_main)
gtest_discover_tests(${TEST_NAME})

if (DEFINED BUILD_SHARED_LIBS_OLD)
    option(BUILD_SHARED_LIBS "Build using shared libraries" ${BUILD_SHARED_LIBS_OLD})
    message(STATUS "STATUS: BUILD_SHARED_LIBS is " ${BUILD_SHARED_LIBS} ", old: " ${BUILD_SHARED_LIBS_OLD})
endif()

if (DEFINED ENABLE_INSTALL AND ENABLE_INSTALL)
    set(INSTALL_GTEST ON CACHE BOOL "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" FORCE)
    if (DEFINED INSTALL_GTEST AND INSTALL_GTEST)
        install(TARGETS ${TEST_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
        install(TARGETS gtest DESTINATION ${CMAKE_INSTALL_BINDIR})
    endif()
endif()