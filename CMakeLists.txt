cmake_minimum_required(VERSION 3.30)
project(arena_allocator CXX)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(arena STATIC src/arena_allocator.cpp)

target_include_directories(arena
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(arena PRIVATE
    -Wall -Werror -Wextra -Wpedantic
)

enable_testing()
add_subdirectory(tests)
