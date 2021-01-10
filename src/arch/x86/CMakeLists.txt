cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE C:\\Users\\ldesp\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake)
project("LWOS_x86" C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(SDL2 CONFIG REQUIRED)

FILE(GLOB_RECURSE SRC_LIST
        ${CMAKE_CURRENT_LIST_DIR}/../../../src/*.*
        )

list(FILTER SRC_LIST EXCLUDE REGEX ".*esp32.*")
list(FILTER SRC_LIST EXCLUDE REGEX ".*cmake.*")

include_directories("${CMAKE_CURRENT_LIST_DIR}/../../../include")

add_compile_definitions(x86)
add_compile_definitions(SCREEN_DRV SDL2)

message(STATUS  ${SRC_LIST})

add_executable(LWOS_x86 ${SRC_LIST})

target_link_libraries(LWOS_x86 PRIVATE SDL2::SDL2main SDL2::SDL2-static)
