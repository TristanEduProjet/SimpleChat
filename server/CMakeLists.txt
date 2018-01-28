file(GLOB_RECURSE srv_src_files ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(schatSrv ${srv_src_files})

target_include_directories(schatSrv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(schatSrv LINK_PUBLIC SChat)

set(EXECUTABLE_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})
