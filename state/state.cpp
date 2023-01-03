#include "state.h"

#include <istream>

State::State(std::istream& input) {
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

void State::readServices(std::istream& input) {
  for (int i = 0; i < service_count_; i++) {
    std::string name;
    binary_id_t bin_id;
    input >> name;
    input >> bin_id;

    service_id_t id = serviceMaintainer().addByName(name);
    binaryMaintainer().getBinary(bin_id).services().insert(id);
  }
}

void State::readFeatures(std::istream& input) {
  for (int i = 0; i < feature_count_; i++) {
    std::string name;
    int num_services_needed;
    int difficulty;
    int users;

    input >> name >> num_services_needed >> difficulty >> users;
    Feature& f = featureMaintainer().getFeature(featureMaintainer().addFeature(name, difficulty, users));
    for (int j = 0; j < num_services_needed; j++) {
      std::string service_name;
      input >> service_name;
      f.services().insert(serviceMaintainer().addByName(service_name));
    }
  }
}

void State::advanceTime(int t) {
  cur_time_ += t;

  serviceMaintainer().advanceTime(t);
  binaryMaintainer().advanceTime(t);
  featureMaintainer().advanceTime(t);
  engineerMaintainer().advanceTime(t);

  scheduled_actions_.advanceTime(t);
  processScheduledActions();
}

void State::processScheduledActions() {
  auto actions = scheduled_actions_.getUnprocessedEvents();
  for (auto& action : actions) {
    action->apply(*this);
  }
}

void State::scheduleAction(int time, std::unique_ptr<Action> action) {
  scheduled_actions_.addEvent(time, std::move(action));
}

void State::countImplementedFeature(feature_id_t id) {
  cur_score_ += featureMaintainer().getFeature(id).users() * std::max<int>(0, time_limit_);
}
