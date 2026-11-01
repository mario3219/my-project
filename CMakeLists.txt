cmake_minimum_required(VERSION 3.10)

project(MyProject LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(myproject OBJECT ${SOURCES})

target_include_directories(myproject PRIVATE include)

target_compile_options(myproject PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    $<$<CONFIG:Debug>:-fsanitize=address>
    $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)
