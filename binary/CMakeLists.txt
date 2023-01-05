set(CMAKE_CXX_STANDARD 17)

link_directories(sol)
link_directories(state)

add_executable(
  run_solution_on_all
  run_solution_on_all.cpp
)

target_link_libraries(
  run_solution_on_all 
  LINK_PUBLIC
  state
  problem_data
  solution
  first_take_action_producer
  producer_based_solver
  solver_interface)

target_include_directories(run_solution_on_all PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(run_solution_on_all PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/sol"
  "${PROJECT_SOURCE_DIR}/source"
)