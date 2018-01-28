file(GLOB_RECURSE cli_src_files ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(schat ${cli_src_files})

target_include_directories(schat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(schat LINK_PUBLIC SChat)

set(EXECUTABLE_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})
