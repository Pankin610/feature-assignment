#include "sol/producer_based_solver.h"
#include "sol/ordered_feature_implementation_producer.h"
#include "state/problem_data.h"

#include <iostream>

int main() {
  auto data = ProblemData::readFromStream(std::cin);
  auto producer = std::make_unique<OrderedFeatureImplementationProducer>(*data);
  auto solver = std::make_unique<ProducerBasedSolver>(std::move(producer));
  auto solution = solver->solve(data);

  std::cout << solution->toString();
  std::cerr << "Score: " << solution->finalState().score() << "\n" << std::endl;

  return 0;
}