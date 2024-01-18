cmake_minimum_required(VERSION 3.22)

project(lfmf)

# when the BUILD_SHARED_LIBS is ON, CMake adds a "lfmf_EXPORTS" define automatically while compiling the library

option(BUILD_SHARED_LIBS "Set to ON (default) to build SHARED libraries" ON)

file(GLOB_RECURSE lfmf_source_files src/*.cpp)
file(GLOB_RECURSE lfmf_header_files include/*.h)

# lfmf will be a shared library (or not) depending on the BUILD_SHARED_LIBS variable

add_library(lfmf ${lfmf_source_files} ${lfmf_header_files})

# for static library, add a "_STATIC_LFMF" define while compiling

target_compile_definitions(lfmf PUBLIC $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:_STATIC_LFMF>)

install(FILES ${lfmf_header_files} DESTINATION include)
install(TARGETS lfmf RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
