cmake_minimum_required(VERSION 3.16)

project(feature-assignment CXX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

include_directories(core)
include_directories(state)
include_directories(sol)
add_subdirectory(sol)
add_subdirectory(state)
link_directories(sol)
link_directories(state)
add_subdirectory(tests)