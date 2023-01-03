#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <queue>

template<typename T>
class EventQueue {
 public:
  EventQueue() {}

  void advanceTime(int t = 1) {
    cur_time_ += t;
  }

  void addEvent(int time, T data) {
    q_.push(Event{.time = time, .data = std::move(data)});
  }

  std::vector<T> getUnprocessedEvents() {
    std::vector<T> data;
    while(!q_.empty() && q_.top().time <= cur_time_) {
      // Have to use const_cast due to bug in std::priority_queue
      data.push_back(std::move(const_cast<Event&>(q_.top()).data));
      q_.pop();
    }
    return data;
  }

 private:
  struct Event {
    int time;
    T data;
    bool operator<(const Event& other) const {
      return time > other.time;
    }
  };

  int cur_time_ = 0;
  std::priority_queue<Event> q_;
};

#endif