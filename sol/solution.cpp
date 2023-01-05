#include "solution.h"

#include <sstream>

void Solution::addEngineerAction(std::unique_ptr<EngineerAction> action) {
  actions_by_eng_[action->getEngId()].push_back(std::move(action));
}

std::string Solution::toString() {
  std::stringstream ss;
  ss << actions_by_eng_.size() << "\n";
  for (const auto& actions : actions_by_eng_) {
    ss << actions.size() << "\n";
    for (const auto& action : actions) {
      ss << action->toString() << "\n";
    }
  }
  return ss.str();
}