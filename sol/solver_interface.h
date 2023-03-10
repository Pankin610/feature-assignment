#ifndef SOLVER_INTERFACE_H
#define SOLVER_INTERFACE_H

#include "state/problem_data.h"
#include "solution.h"
#include <memory>

class SolverInterface {
 public:
  virtual std::unique_ptr<Solution> solve(std::shared_ptr<ProblemData> data) = 0;
  virtual ~SolverInterface() {}
};

#endif