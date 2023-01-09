#ifndef PROBLEM_DATA_H
#define PROBLEM_DATA_H

#include "id_maintainer.h"
#include "binary_maintainer.h"
#include "feature_maintainer.h"
#include "core/types.h"
#include <memory>
#include <istream>
#include <ostream>

class ProblemData {
 public:

  ProblemData(int time_limit, int eng_count, int binary_count, int binary_creation_time) :
    time_limit_(time_limit),
    eng_count_(eng_count),
    binary_count_(binary_count),
    binary_creation_time_(binary_creation_time),
    binary_maintainer_(binary_count),
    engineer_maintainer_(eng_count) {}

  static std::shared_ptr<ProblemData> readFromStream(std::istream& input) {
    return std::shared_ptr<ProblemData>(new ProblemData(input));
  }

  const BinaryMaintainer& binaryMaintainer() const {
    return binary_maintainer_;
  }

  const FeatureMaintainer& featureMaintainer() const {
    return feature_maintainer_;
  }

  const IdMaintainer& engineerMaintainer() const {
    return engineer_maintainer_;
  }

  const IdMaintainer& serviceMaintainer() const {
    return service_maintainer_;
  }

  int timeToMakeBin() const {
    return binary_creation_time_;
  }

  int timeLimit() const {
    return time_limit_;
  }

 private:
  ProblemData(std::istream& input);
  void readServices(std::istream& input);
  void readFeatures(std::istream& input);

  int time_limit_;
  int eng_count_;
  int service_count_;
  int binary_count_;
  int feature_count_;
  int binary_creation_time_;

  BinaryMaintainer binary_maintainer_;
  FeatureMaintainer feature_maintainer_;
  IdMaintainer engineer_maintainer_;
  IdMaintainer service_maintainer_;
};

std::ostream& operator<<(std::ostream& out, const ProblemData& data);

#endif