#include <gtest/gtest.h>

#include "state/problem_data.h"
#include "sol/first_take_action_producer.h"
#include "sol/producer_based_solver.h"
#include "sol/solution.h"

#include <fstream>

TEST(ProducerBasedSolverTests, TestFromStatement) {
  std::ifstream inp("hashcode_tests/a_example.in.txt");
  auto data = ProblemData::readFromStream(inp);
  EXPECT_EQ(data->binaryMaintainer().numBinaries(), 3);

  auto producer = std::make_unique<FirstTakeActionProducer>();
  ProducerBasedSolver solver(std::move(producer));
  auto solution = solver.solve(data);
  const State& final_state = solution->finalState();
  EXPECT_EQ(final_state.score(), 540);
  EXPECT_EQ(solution->getEngineerActions(0).at(0)->toString(), "impl foo 1");
  EXPECT_EQ(solution->getEngineerActions(0).at(1)->toString(), "impl bar 1");
  EXPECT_EQ(solution->getEngineerActions(1).at(0)->toString(), "impl foo 2");
}