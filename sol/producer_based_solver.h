#ifndef PRODUCER_BASED_SOLVER_H
#define PRODUCER_BASED_SOLVER_H

#include "state/action.h"
#include "state/state.h"
#include "solver_interface.h"
#include "action_producer_interface.h"
#include "solution.h"

#include <memory>

class ProducerBasedSolver : public SolverInterface {
 public:
  ProducerBasedSolver(std::unique_ptr<ActionProducerInterface> producer) :
    producer_(std::move(producer)) {}

  std::unique_ptr<Solution> solve(std::shared_ptr<ProblemData> data) override;

 private:
  bool makeAction(State& state);

  std::unique_ptr<ActionProducerInterface> producer_;
  std::unique_ptr<Solution> solution_;
};

#endif