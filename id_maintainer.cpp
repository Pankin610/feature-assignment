#include "id_maintainer.h"

int IdMaintainer::addId() {
  int new_id = last_id_++;
  available_ids_.insert(new_id);
  return new_id;
}

int IdMaintainer::addByName(const std::string& name) {
  auto it = id_by_name_.find(name);
  if (it != id_by_name_.end()) {
    return it->second;
  }

  int new_id = addId();
  id_by_name_[name] = new_id;
  return new_id;
}

void IdMaintainer::removeId(int id) {
  auto it = available_ids_.find(id);
  if (it == available_ids_.end()) {
    throw std::runtime_error("Id not available or already removed.");
  }
  available_ids_.erase(it);
}

void IdMaintainer::suspendId(int id, int duration) {
  removeId(id);
  add_id_event_q_.addEvent(cur_time_ + duration, id);
}

const id_container_t& IdMaintainer::getAvailableIds() const {
  return available_ids_;
}

bool IdMaintainer::isAvailable(int id) const {
  return available_ids_.find(id) != available_ids_.end();
}

void IdMaintainer::advanceTime(int days) {
  add_id_event_q_.advanceTime(days);
  goThroughEvents();
}

void IdMaintainer::goThroughEvents() {
  auto restored_ids = add_id_event_q_.getUnprocessedEvents();
  for (int& id : restored_ids) {
    available_ids_.insert(id);
  }
}


