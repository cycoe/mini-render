cmake_minimum_required(VERSION 3.14)

project(mini-renderer)

set(CMAKE_EXPORT_COMPILE_COMMANDS "yes")

include_directories(inc)
aux_source_directory(src SRCS)
add_subdirectory(test)

add_executable(mini-renderer ${SRCS})
