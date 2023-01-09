#ifndef BINARY_MAINTAINER_H
#define BINARY_MAINTAINER_H

#include "core/binary.h"
#include "id_maintainer.h"
#include <set>
#include <queue>

class BinaryMaintainer {
 public:
  BinaryMaintainer(int n = 0) {
    binary_by_id_.reserve(2 * n);
    while(n--) {
      addBinary();
    }
  }

  binary_id_t addBinary() {
    binary_id_t id = id_maintainer_.addId();
    num_workers_.insert(std::make_pair(id, 0));
    binary_by_id_.emplace_back(id);
    return id;
  }

  Binary& getBinary(binary_id_t id) {
    return binary_by_id_[id];
  }

  void addService(binary_id_t bin_id, service_id_t service_id) {
    binary_for_service_[service_id] = bin_id;
    getBinary(bin_id).services().insert(service_id);
  }

  binary_id_t getBinaryIdForService(service_id_t service) const {
    return binary_for_service_.at(service);
  }

  int moveService(service_id_t service, binary_id_t new_bin_id) {
    binary_id_t old_bin_id = new_bin_id;
    if (old_bin_id == new_bin_id) {
      return 0;
    }

    int dur = std::max(getBinary(new_bin_id).services().size(), getBinary(old_bin_id).services().size());
    blockBinary(old_bin_id, dur);
    blockBinary(new_bin_id, dur);
    getBinary(new_bin_id).services().insert(service);
    getBinary(old_bin_id).services().erase(service);
    return dur;
  }

  void blockBinary(binary_id_t id, int duration) {
    if (numWorkersOnBinary(id) > 0) {
      throw std::runtime_error("Can't block binary that's being processed.");
    }
    id_maintainer_.suspendId(id, duration);
  }

  void workOnBinary(binary_id_t id) {
    num_workers_.at(id)++;
  }

  void stopWorkingOnBinary(binary_id_t id) {
    num_workers_.at(id)--;
  }

  int numWorkersOnBinary(binary_id_t id) const {
    return num_workers_.at(id);
  }

  const id_container_t& getAvailableBinaries() const {
    return id_maintainer_.getAvailableIds();
  }

  void advanceTime(int days = 1) {
    id_maintainer_.advanceTime(days);
  }

  int numBinaries() const {
    return id_maintainer_.numIds();
  }

 private:
  IdMaintainer id_maintainer_;
  std::vector<Binary> binary_by_id_;
  std::unordered_map<binary_id_t, int> num_workers_;
  std::unordered_map<service_id_t, binary_id_t> binary_for_service_;
};

#endif