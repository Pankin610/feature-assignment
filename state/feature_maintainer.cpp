#include "feature_maintainer.h"

feature_id_t FeatureMaintainer::addFeature(const std::string& name, int difficulty, int users) {
  feature_id_t id = getFeatureId(name);
  feature_by_id_.emplace_back(name, id, difficulty, users);
  return id;
}

bool FeatureMaintainer::implementInBinary(feature_id_t id, const Binary& binary) {
  Feature& f = getFeature(id);
  for (service_id_t service : binary.services()) {
    f.services().erase(service);
  }
  if (f.services().empty()) {
    implement(id);
    return true;
  }
  return false;
}
