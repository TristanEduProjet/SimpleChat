#project(libschat)

file(GLOB_RECURSE lib_src_files ${CMAKE_CURRENT_SOURCE_DIR}/*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(SChat SHARED ${lib_src_files})
#target_include_directories(SChat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})
