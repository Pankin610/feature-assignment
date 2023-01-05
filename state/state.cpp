#include "state.h"
#include "problem_data.h"

#include <istream>

void State::copyFromData() {
  binary_maintainer_ = data_->binaryMaintainer();
  engineer_maintainer_ = data_->engineerMaintainer();
  feature_maintainer_ = data_->featureMaintainer();
  service_maintainer_ = data_->serviceMaintainer();
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

std::set<binary_id_t> State::binariesForFeature(feature_id_t feature_id) const {
  std::set<binary_id_t> binaries;
  for (service_id_t service : featureMaintainer().getFeature(feature_id).services()) {
    binaries.insert(binaryMaintainer().getBinaryIdForService(service));
  }
  return binaries;
}
