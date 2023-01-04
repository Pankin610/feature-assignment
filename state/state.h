#ifndef STATE_H
#define STATE_H

#include "binary_maintainer.h"
#include "feature_maintainer.h"
#include "types.h"
#include "event_queue.h"
#include "action.h"
#include <istream>
#include <memory>

class Action;

class State {
 public:
  static State readFromStream(std::istream& input) {
    return State(input);
  }

  State(int time_limit, int eng_count, int binary_count, int binary_creation_time) :
    time_limit_(time_limit),
    eng_count_(eng_count),
    binary_count_(binary_count),
    binary_creation_time_(binary_creation_time),
    binary_maintainer_(binary_count),
    engineer_maintainer_(eng_count) {}

  void advanceTime(int t = 1);

  BinaryMaintainer& binaryMaintainer() {
    return binary_maintainer_;
  }

  FeatureMaintainer& featureMaintainer() {
    return feature_maintainer_;
  }

  IdMaintainer& engineerMaintainer() {
    return engineer_maintainer_;
  }

  IdMaintainer& serviceMaintainer() {
    return service_maintainer_;
  }

  bool isFinished() const {
    return cur_time_ >= time_limit_;
  }

  int score() const {
    return cur_score_;
  }

  int& score() {
    return cur_score_;
  }

  int timeToMakeBin() const {
    return binary_creation_time_;
  }

  int curTime() const {
    return cur_time_;
  }

  int timeLimit() const {
    return time_limit_;
  }

  void countImplementedFeature(feature_id_t id);

  void scheduleAction(int time, std::unique_ptr<Action> action);

 private:
  State(std::istream& input);
  void readServices(std::istream& input);
  void readFeatures(std::istream& input);
  void processScheduledActions();

  int cur_time_ = 0;
  int cur_score_ = 0;
  int time_limit_;
  int eng_count_;
  int service_count_;
  int binary_count_;
  int feature_count_;
  int binary_creation_time_;

  BinaryMaintainer binary_maintainer_;
  FeatureMaintainer feature_maintainer_;
  IdMaintainer engineer_maintainer_;
  IdMaintainer service_maintainer_;

  EventQueue<std::unique_ptr<Action>> scheduled_actions_;
};

#endif