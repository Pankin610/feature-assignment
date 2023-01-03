cmake_minimum_required(VERSION 3.16)

project(feature-assignment)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

include_directories(core)
include_directories(state)
add_subdirectory(tests)
add_subdirectory(state)
