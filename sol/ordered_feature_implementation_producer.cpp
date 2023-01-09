#include "ordered_feature_implementation_producer.h"

OrderedFeatureImplementationProducer::OrderedFeatureImplementationProducer(const ProblemData& data) {
  for (feature_id_t id : data.featureMaintainer().getUnimplementedFeatures()) {
    feature_order_.push_back(id);
  }
  State temp_state(std::shared_ptr<ProblemData>(new ProblemData(data)));
  std::sort(feature_order_.begin(), feature_order_.end(), [&](feature_id_t id1, feature_id_t id2) {
    const Feature& feature1 = data.featureMaintainer().getFeature(id1);
    const Feature& feature2 = data.featureMaintainer().getFeature(id2);

    return static_cast<double>(feature1.users()) / (feature1.difficulty() * temp_state.binariesForFeature(id1).size()) > 
           static_cast<double>(feature2.users()) / (feature2.difficulty() * temp_state.binariesForFeature(id2).size());
  });
}

AccumulateAction<EngineerAction> OrderedFeatureImplementationProducer::getNextAction(State& state) {
  AccumulateAction<EngineerAction> accum_action;
  auto available_engineers = state.engineerMaintainer().getAvailableIds();
  for (engineer_id_t eng : available_engineers) {
    auto action = takeFirstActionInOrder(eng, state);
    action->apply(state);
    accum_action.addAction(std::move(action));
  }
  return accum_action;
}

std::unique_ptr<EngineerAction> OrderedFeatureImplementationProducer::takeFirstActionInOrder(
  engineer_id_t id, State& state)
{
  for (feature_id_t feature_id : feature_order_) {
    const auto& unimplemented = state.featureMaintainer().getUnimplementedFeatures();
    if (unimplemented.find(feature_id) == unimplemented.end()) {
      continue;
    }

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
