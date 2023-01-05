cmake_minimum_required(VERSION 3.16)

project(feature-assignment CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(solution SHARED solution.cpp solution.h)

add_library(action_producer_interface INTERFACE)
add_library(first_take_action_producer SHARED first_take_action_producer.cpp first_take_action_producer.h)

add_library(solver_interface INTERFACE)
add_library(producer_based_solver SHARED producer_based_solver.cpp producer_based_solver.h)

target_include_directories(solution PUBLIC .)
target_include_directories(solver_interface INTERFACE .)
target_include_directories(action_producer_interface INTERFACE .)