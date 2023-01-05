include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)


add_executable(
  unit_tests
  binary_maintainer_test.cpp
  feature_maintainer_test.cpp
  state_test.cpp
)

find_library(MYLIB_LIBRARY id_maintainer)
target_link_libraries(
  unit_tests 
  gtest_main
  id_maintainer
  feature_maintainer
  state
  problem_data)

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(unit_tests)