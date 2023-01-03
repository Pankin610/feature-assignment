cmake_minimum_required(VERSION 3.16)

project(feature-assignment)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

enable_testing()

add_library(id_maintainer SHARED id_maintainer.cpp id_maintainer.h)
add_library(feature_maintainer SHARED feature_maintainer.cpp feature_maintainer.h)

add_executable(
  unit_tests
  binary_maintainer_test.cpp
  feature_maintainer_test.cpp
)

target_link_libraries(
  unit_tests
  gtest_main
  id_maintainer
  feature_maintainer
)

include(GoogleTest)
gtest_discover_tests(unit_tests)