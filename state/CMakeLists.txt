cmake_minimum_required(VERSION 3.16)

project(feature-assignment)

set(CMAKE_CXX_STANDARD 17)

add_library(id_maintainer SHARED id_maintainer.cpp id_maintainer.h)
add_library(feature_maintainer SHARED feature_maintainer.cpp feature_maintainer.h)
add_library(state SHARED state.cpp action.cpp state.h action.h)

target_include_directories(id_maintainer PRIVATE .)
target_include_directories(feature_maintainer PRIVATE .)
target_include_directories(state PRIVATE .)