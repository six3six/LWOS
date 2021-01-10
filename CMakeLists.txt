# !!! WARNING !!! AUTO-GENERATED FILE, PLEASE DO NOT MODIFY IT AND USE
# https://docs.platformio.org/page/projectconf/section_env_build.html#build-flags
#
# If you need to override existing CMake configuration or add extra,
# please create `CMakeListsUser.txt` in the root of project.
# The `CMakeListsUser.txt` will not be overwritten by PlatformIO.

cmake_minimum_required(VERSION 3.13)

project(LWOS C CXX)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_BUILD_TYPE MATCHES "x86")
    set(CMAKE_BUILD_TYPE Debug)

    find_package(SDL2 CONFIG REQUIRED)

    FILE(GLOB_RECURSE SRC_LIST
            ${CMAKE_CURRENT_LIST_DIR}/src/*.*
            )

    list(FILTER SRC_LIST EXCLUDE REGEX ".*esp32.*")
    list(FILTER SRC_LIST EXCLUDE REGEX ".*cmake.*")

    include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

    add_compile_definitions(x86)
    add_compile_definitions(SCREEN_DRV SDL2)

    add_executable(LWOS ${SRC_LIST})

    target_link_libraries(LWOS PRIVATE SDL2::SDL2main SDL2::SDL2-static)

else ()

    include(CMakeListsPrivate.txt)

    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsUser.txt)
        include(CMakeListsUser.txt)
    endif ()

    add_custom_target(
            Production ALL
            COMMAND platformio -c clion run "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    add_custom_target(
            Debug ALL
            COMMAND platformio -c clion run --target debug "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    add_executable(Z_DUMMY_TARGET ${SRC_LIST})

endif ()