#ifndef SOLVER_INTERFACE_H
#define SOLVER_INTERFACE_H

#include "problem_data.h"
#include "solution.h"
#include <memory>

class SolverInterface {
 public:
  virtual std::unique_ptr<Solution> solve(std::shared_ptr<ProblemData> data);
  virtual ~SolverInterface() {}
};

#endif