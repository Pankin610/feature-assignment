#ifndef FEATURE_H
#define FEATURE_H

#include "types.h"
#include <vector>
#include <string>

class Feature {
 public:
  Feature(feature_id_t id, int difficulty, int users) : 
    id_(id),
    difficulty_(difficulty),
    users_(users) {}

  feature_id_t id() const {
    return id_;
  }

  int users() const {
    return users_;
  }

  int difficulty() const {
    return difficulty_;
  }

  id_container_t& services() {
    return services_;
  }

  const id_container_t& services() const {
    return services_;
  }

 private:
  feature_id_t id_;
  int difficulty_;
  int users_;
  id_container_t services_;
};

#endif
