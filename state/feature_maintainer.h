#ifndef FEATURE_MAINTAINER_H
#define FEATURE_MAINTAINER_H

#include "binary.h"
#include "feature.h"
#include "id_maintainer.h"
#include <set>
#include <queue>
#include <string>

class FeatureMaintainer {
 public:
  feature_id_t addFeature(const std::string& name, int difficulty, int users);

  feature_id_t getFeatureId(const std::string& name) {
    return id_maintainer_.addByName(name);
  }

  Feature& getFeature(feature_id_t id) {
    return feature_by_id_[id];
  }

  const Feature& getFeature(feature_id_t id) const {
    return feature_by_id_[id];
  }

  std::string getFeatureName(feature_id_t id) const {
    return id_maintainer_.getName(id);
  }

  bool implementInBinary(feature_id_t id, const Binary& binary);

  void implement(feature_id_t id) {
    id_maintainer_.removeId(id);
  }

  const id_container_t& getUnimplementedFeatures() const {
    return id_maintainer_.getAvailableIds();
  }

  void advanceTime(int days = 1) {
    id_maintainer_.advanceTime(days);
  }

 private:
  IdMaintainer id_maintainer_;
  std::vector<Feature> feature_by_id_;
};

#endif