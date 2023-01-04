#ifndef FEATURE_H
#define FEATURE_H

#include "types.h"
#include <vector>
#include <string>

class Feature {
 public:
  Feature(std::string name, feature_id_t id, int difficulty, int users) : 
    name_(std::move(name)),
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

  const std::string& name() const {
    return name_;
  }
  
 private:
  std::string name_;
  feature_id_t id_;
  int difficulty_;
  int users_;
  id_container_t services_;
};

#endif
