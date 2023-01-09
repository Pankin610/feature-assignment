#include "action.h"

#include <memory>
#include <sstream>

void ImplementFeatureAction::apply(State& state) {
  const Binary& binary = state.binaryMaintainer().getBinary(bin_id_);
  if (state.featureMaintainer().implementInBinary(feature_id_, binary)) {
    int time_in_prod = std::max<int>(0, state.timeLimit() - time_done_);
    state.score() += state.featureMaintainer().getFeature(feature_id_).users() * time_in_prod;
  }
  auto it = state.featuresInProgress().find(std::make_pair(feature_id_, bin_id_));
  if (it == state.featuresInProgress().end()) {
    throw std::runtime_error("Feature not in progress of implementation.");
  }
  state.featuresInProgress().erase(it);
  state.binaryMaintainer().stopWorkingOnBinary(bin_id_);
}

void StartImplementingFeatureAction::apply(State& state) {
  const Binary& binary = state.binaryMaintainer().getBinary(bin_id_);
  if (state.featuresInProgress().find(std::make_pair(feature_id_, bin_id_)) != state.featuresInProgress().end()) {
    throw std::runtime_error("Feature already in progress in this binary.");
  }
  state.featuresInProgress().insert(std::make_pair(feature_id_, bin_id_));

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
  state.binaryMaintainer().workOnBinary(bin_id_);
}

std::string StartImplementingFeatureAction::toString() const {
  std::string feature_name = data_->featureMaintainer().getFeatureName(feature_id_);
  std::stringstream ss;
  ss << "impl ";
  ss << feature_name;
  ss << " " << bin_id_;
  return ss.str();
}

void EngineerSleepAction::apply(State& state) {
  state.engineerMaintainer().suspendId(eng_id_, duration_);
}

std::string EngineerSleepAction::toString() const {
  std::stringstream ss;
  ss << "wait ";
  ss << duration_;
  return ss.str();
}

void MoveServiceAction::apply(State& state) {
  int duration = state.binaryMaintainer().moveService(service_id_, bin_id_);
  state.engineerMaintainer().suspendId(eng_id_, duration);
}

std::string MoveServiceAction::toString() const {
  std::string service_name = data_->serviceMaintainer().getName(service_id_);
  std::stringstream ss;
  ss << "move ";
  ss << service_name << " ";
  ss << bin_id_;
  return ss.str();
}

void CreateBinaryAction::apply(State& state) {
  int duration = state.timeToMakeBin();
  binary_id_t new_bin = state.binaryMaintainer().addBinary();
  
  state.engineerMaintainer().suspendId(eng_id_, duration);
  state.binaryMaintainer().blockBinary(new_bin, duration);
}

std::string CreateBinaryAction::toString() const {
  return "new";
}