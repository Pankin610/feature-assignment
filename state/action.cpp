#include "action.h"

#include <memory>
#include <sstream>

void ImplementFeatureAction::apply(State& state) {
  Binary& binary = state.binaryMaintainer().getBinary(bin_id_);
  if (state.featureMaintainer().implementInBinary(feature_id_, binary)) {
    int time_in_prod = std::max<int>(0, state.timeLimit() - time_done_);
    state.score() += state.featureMaintainer().getFeature(feature_id_).users() * time_in_prod;
  }
}

void StartImplementingFeatureAction::apply(State& state) {
  Binary& binary = state.binaryMaintainer().getBinary(bin_id_);
  int duration = 
    state.featureMaintainer().getFeature(feature_id_).difficulty() +
    state.binaryMaintainer().numWorkersOnBinary(bin_id_) +
    binary.services().size();

  state.engineerMaintainer().suspendId(eng_id_, duration);
  int time_when_done = state.curTime() + duration;
  state.scheduleAction(
    time_when_done, 
    std::make_unique<ImplementFeatureAction>(feature_id_, bin_id_, time_when_done)
  );
}

std::string StartImplementingFeatureAction::toString(State& state) const {
  std::string feature_name = state.featureMaintainer().getFeature(feature_id_).name();
  std::stringstream ss;
  ss << "impl ";
  ss << feature_name;
  ss << " " << bin_id_;
  return ss.str();
}

void EngineerSleepAction::apply(State& state) {
  state.engineerMaintainer().suspendId(eng_id_, duration_);
}

void MoveServiceAction::apply(State& state) {
  int duration = state.binaryMaintainer().moveService(service_id_, bin_id_);
  state.engineerMaintainer().suspendId(eng_id_, duration);
}

void AccumulateAction::apply(State& state) {
  for (const auto& action : actions_) {
    action->apply(state);
  }
}