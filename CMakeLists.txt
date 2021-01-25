cmake_minimum_required(VERSION 3.10)
#set (CMAKE_CXX_COMPILER "/usr/bin/clang++")
set (CMAKE_CXX_COMPILER "/data1/zhangyuanyuan22/usr/bin/clang++")
project(ray_tracing CXX)

add_compile_options(
    -g
    -std=c++2a
)
include_directories(
    ./include
)

aux_source_directory(
    ./src
    src_list
)

add_executable(out ${src_list})