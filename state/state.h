#ifndef STATE_H
#define STATE_H

#include "binary_maintainer.h"
#include "feature_maintainer.h"
#include "types.h"
#include "event_queue.h"
#include "action.h"
#include "problem_data.h"

#include <istream>
#include <memory>

class Action;

class State {
 public:
  static State readFromStream(std::istream& input) {
    return State(input);
  }

  State(std::shared_ptr<ProblemData> data) : data_(std::move(data)) {
    copyFromData();
  }

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

  const BinaryMaintainer& binaryMaintainer() const {
    return binary_maintainer_;
  }

  const FeatureMaintainer& featureMaintainer() const {
    return feature_maintainer_;
  }

  const IdMaintainer& engineerMaintainer() const {
    return engineer_maintainer_;
  }

  const IdMaintainer& serviceMaintainer() const {
    return service_maintainer_;
  }

  bool isFinished() const {
    return cur_time_ >= data_->timeLimit();
  }

  int score() const {
    return cur_score_;
  }

  int& score() {
    return cur_score_;
  }

  int timeToMakeBin() const {
    return data_->timeToMakeBin();
  }

  int curTime() const {
    return cur_time_;
  }

  int timeLimit() const {
    return data_->timeLimit();
  }

  void countImplementedFeature(feature_id_t id);

  void scheduleAction(int time, std::unique_ptr<Action> action);

  std::set<std::pair<feature_id_t, binary_id_t>>& featuresInProgress() {
    return features_in_progress_;
  }

  std::set<binary_id_t> binariesForFeature(feature_id_t feature_id) const;

  std::shared_ptr<ProblemData> problemData() const {
    return data_;
  }

 private:
  State(std::istream& input) : data_(ProblemData::readFromStream(input)) {
    copyFromData();
  }
  
  void copyFromData();
  void processScheduledActions();

  int cur_time_ = 0;
  int cur_score_ = 0;
  std::shared_ptr<ProblemData> data_;

  BinaryMaintainer binary_maintainer_;
  FeatureMaintainer feature_maintainer_;
  IdMaintainer engineer_maintainer_;
  IdMaintainer service_maintainer_;

  std::set<std::pair<feature_id_t, binary_id_t>> features_in_progress_;

  EventQueue<std::unique_ptr<Action>> scheduled_actions_;
};

#endif