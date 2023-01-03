#ifndef BINARY_H
#define BINARY_H

#include "types.h"
#include <vector>

class Binary {
 public:
  Binary(int id) : id_(id) {}

  int id() const {
    return id_;
  }

  id_container_t& services() {
    return services_;
  }

  const id_container_t& services() const {
    return services_;
  }

 private:
  binary_id_t id_;
  id_container_t services_;
};

#endif