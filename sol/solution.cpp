#include "solution.h"

#include <sstream>

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