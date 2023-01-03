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

add_executable(
  unit_tests
  feature_maintainer_test.cpp
  binary_maintainer_test.cpp
)

target_link_libraries(
  unit_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)