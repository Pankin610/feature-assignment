#ifndef SOLUTION_H
#define SOLUTION_H

#include "action.h"

class Solution {
 public:
  Solution(int eng_count) : actions_by_eng_(eng_count) {}

  const std::vector<std::unique_ptr<EngineerAction>>& 
      getEngineerActions(engineer_id_t eng_id) const {
    return actions_by_eng_[eng_id];
  }

  std::string toString();

  void addEngineerAction(std::unique_ptr<EngineerAction> action);
 private:
  std::vector<std::vector<std::unique_ptr<EngineerAction>>> actions_by_eng_;
};

#endif