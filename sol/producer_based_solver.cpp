#include "producer_based_solver.h"

std::unique_ptr<Solution> ProducerBasedSolver::solve(std::shared_ptr<ProblemData> data) {
  solution_ = std::make_unique<Solution>(data->engineerMaintainer().numIds());
  State state(data);
  while(makeAction(state));

  return std::move(solution_);
}

bool ProducerBasedSolver::makeAction(State& state) {
  if (state.curTime() >= state.timeLimit()) {
    return false;
  }

  auto next_action = producer_->getNextAction(state);
  next_action.apply(state);
  state.advanceTime();
  return true;
}

