#include "producer_based_solver.h"

std::unique_ptr<Solution> ProducerBasedSolver::solve(std::shared_ptr<ProblemData> data) {
  solution_ = std::make_unique<Solution>(data->engineerMaintainer().numIds());
  auto state = std::make_unique<State>(data);

  while(makeAction(*state));

  solution_->setFinalState(std::move(state));
  return std::move(solution_);
}

bool ProducerBasedSolver::makeAction(State& state) {
  if (state.curTime() >= state.timeLimit()) {
    return false;
  }

  auto next_action = producer_->getNextAction(state);
  state.advanceTime();
  for (auto& action : next_action.actions()) {
    solution_->addEngineerAction(std::move(action));
  }
  return true;
}

