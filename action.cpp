#include "action.h"

#include <memory>

void ImplementFeatureAction::apply(State& state) {
  Binary& binary = state.binaryMaintainer().getBinary(bin_id_);
  if (state.featureMaintainer().implementInBinary(feature_id_, binary)) {
    state.countImplementedFeature(feature_id_);
  }
}

void StartImplementingFeatureAction::apply(State& state) {
  Binary& binary = state.binaryMaintainer().getBinary(bin_id_);
  int duration = 
    state.featureMaintainer().getFeature(feature_id_).difficulty() +
    state.binaryMaintainer().numWorkersOnBinary(bin_id_) +
    binary.services().size();

  state.engineerMaintainer().suspendId(eng_id_, duration);
  state.scheduleAction(
    state.curTime() + duration, 
    std::make_unique<ImplementFeatureAction>(feature_id_, bin_id_)
  );
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