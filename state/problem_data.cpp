#include "problem_data.h"

#include <iostream>

ProblemData::ProblemData(std::istream& input) {
  input >> time_limit_;
  input >> eng_count_;
  engineer_maintainer_ = IdMaintainer(eng_count_);
  input >> service_count_;
  input >> binary_count_;
  binary_maintainer_ = BinaryMaintainer(binary_count_);
  input >> feature_count_;
  input >> binary_creation_time_;

  readServices(input);
  readFeatures(input);
}

void ProblemData::readServices(std::istream& input) {
  for (int i = 0; i < service_count_; i++) {
    std::string name;
    binary_id_t bin_id;
    input >> name;
    input >> bin_id;

    service_id_t id = service_maintainer_.addByName(name);
    binary_maintainer_.addService(bin_id, id);
  }
}

void ProblemData::readFeatures(std::istream& input) {
  for (int i = 0; i < feature_count_; i++) {
    std::string name;
    int num_services_needed;
    int difficulty;
    int users;

    input >> name >> num_services_needed >> difficulty >> users;
    Feature& f = feature_maintainer_.getFeature(feature_maintainer_.addFeature(name, difficulty, users));
    for (int j = 0; j < num_services_needed; j++) {
      std::string service_name;
      input >> service_name;
      f.services().insert(service_maintainer_.addByName(service_name));
    }
  }
}