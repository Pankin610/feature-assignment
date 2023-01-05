#include "first_take_action_producer.h"

AccumulateAction<EngineerAction> FirstTakeActionProducer::getNextAction(State& state) {
  AccumulateAction<EngineerAction> accum_action;
  auto available_engineers = state.engineerMaintainer().getAvailableIds();
  for (engineer_id_t eng : available_engineers) {
    auto action = takeFirstActionForEngineer(eng, state);
    action->apply(state);
    accum_action.addAction(std::move(action));
  }
  return accum_action;
}

std::unique_ptr<EngineerAction> FirstTakeActionProducer::takeFirstActionForEngineer(
  engineer_id_t id, State& state)
{
  for (feature_id_t feature_id : state.featureMaintainer().getUnimplementedFeatures()) {
    std::set<binary_id_t> binaries = state.binariesForFeature(feature_id);
    for (binary_id_t bin_id : binaries) {
      if (state.featuresInProgress().find(std::make_pair(feature_id, bin_id)) != 
          state.featuresInProgress().end()) {
        continue;
      }
      return std::make_unique<StartImplementingFeatureAction>(id, feature_id, bin_id, state.problemData());
    }
  }
  return std::make_unique<EngineerSleepAction>(id);
}
