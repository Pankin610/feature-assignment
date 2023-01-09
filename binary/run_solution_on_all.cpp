#include "sol/producer_based_solver.h"
#include "sol/first_take_action_producer.h"
#include "state/problem_data.h"

#include <iostream>

int main() {
  auto data = ProblemData::readFromStream(std::cin);
  auto producer = std::make_unique<FirstTakeActionProducer>();
  auto solver = std::make_unique<ProducerBasedSolver>(std::move(producer));
  auto solution = solver->solve(data);

  std::cout << solution->toString();

  return 0;
}