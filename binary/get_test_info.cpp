#include "state/problem_data.h"

#include <iostream>

int main() {
  auto data = ProblemData::readFromStream(std::cin);
  std::cout << *data;

  return 0;
}