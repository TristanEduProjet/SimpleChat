cmake_minimum_required(VERSION 3.0)
project(SimpleChat VERSION 0.0.1)

option(BUILD_CLIENT "Enable building client app" ON)
option(BUILD_SERVER "Enable building server prog" ON)
#but the lib is necessary for both, so not an option

set(LIBRARY_OUTPUT_PATH build/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH build/${CMAKE_BUILD_TYPE})

file(GLOB_RECURSE lib_src_files ${CMAKE_CURRENT_SOURCE_DIR}/common/*)
add_library(SChat SHARED ${lib_src_files})
target_include_directories(SChat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_SERVER)
    file(GLOB_RECURSE srv_src_files ${CMAKE_CURRENT_SOURCE_DIR}/server/*)
    add_executable(schatSrv ${srv_src_files})
    target_include_directories(schatSrv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/server)
    target_link_libraries(schatSrv LINK_PUBLIC SChat)
endif()

if(BUILD_CLIENT)
    file(GLOB_RECURSE cli_src_files ${CMAKE_CURRENT_SOURCE_DIR}/client/*)
    add_executable(schatCli ${cli_src_files})
    target_include_directories(schatCli PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/client)
    target_link_libraries(schatCli LINK_PUBLIC SChat)
endif()
