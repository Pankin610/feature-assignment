#ifndef SOLUTION_H
#define SOLUTION_H

#include "action.h"

#include <memory>
#include <vector>
#include <string>

class Solution {
 public:
  Solution(int eng_count) : actions_by_eng_(eng_count) {}

  const std::vector<std::unique_ptr<EngineerAction>>& 
      getEngineerActions(engineer_id_t eng_id) const {
    return actions_by_eng_[eng_id];
  }

  std::string toString();

  void addEngineerAction(std::unique_ptr<EngineerAction> action) {
    actions_by_eng_[action->getEngId()].push_back(std::move(action));
  }

  void setFinalState(std::unique_ptr<State> state) {
    final_state_ = std::move(state);
  }

  const State& finalState() const {
    return *final_state_;
  }

 private:
  std::vector<std::vector<std::unique_ptr<EngineerAction>>> actions_by_eng_;
  std::unique_ptr<State> final_state_;
};

#endif