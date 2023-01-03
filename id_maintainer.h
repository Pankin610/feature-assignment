#ifndef ID_MAINTAINER_H
#define ID_MAINTAINER_H

#include <string>
#include <queue>
#include <unordered_map>

#include "types.h"
#include "event_queue.h"

class IdMaintainer {
 public:
  IdMaintainer(int n = 0) : cur_time_(0), last_id_(0) {
    while(n--) {
      addId();
    }
  }
  int addId();

  int addByName(const std::string& name);

  void removeId(int id);

  void suspendId(int id, int duration);

  const id_container_t& getAvailableIds() const;

  bool isAvailable(int id) const;

  void advanceTime(int days = 1);

 private:
  void goThroughEvents();

  int cur_time_;
  id_container_t available_ids_;
  std::unordered_map<std::string, int> id_by_name_;
  int last_id_;
  EventQueue<int> add_id_event_q_;
};

#endif