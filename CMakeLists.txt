cmake_minimum_required(VERSION 3.15)
project(ring_buffer)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "includes/*.h" "includes/*.hpp" "src/*.c" "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(includes)
