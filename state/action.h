#ifndef ACTION_H
#define ACTION_H

#include "state.h"
#include "feature.h"
#include "types.h"

class State;

class Action {
 public:
  virtual void apply(State& state) = 0;
  virtual ~Action() = 0;
};

class ImplementFeatureAction : public Action {
 public:
  ImplementFeatureAction(feature_id_t feature_id, binary_id_t bin_id) :
    feature_id_(feature_id),
    bin_id_(bin_id) {}
    
  void apply(State& state) override;

 private:
  feature_id_t feature_id_;
  binary_id_t bin_id_;
};

class StartImplementingFeatureAction : public Action {
 public:
  StartImplementingFeatureAction(engineer_id_t eng_id, feature_id_t feature_id, binary_id_t bin_id) :
    eng_id_(eng_id),
    feature_id_(feature_id),
    bin_id_(bin_id) {}
    
  void apply(State& state) override;

 private:
  engineer_id_t eng_id_;
  feature_id_t feature_id_;
  binary_id_t bin_id_;
};

class EngineerSleepAction : public Action {
 public:
  EngineerSleepAction(engineer_id_t eng_id, int duration = 1) :
    eng_id_(eng_id),
    duration_(duration) {}

  void apply(State& state) override;

 private:
  engineer_id_t eng_id_;
  int duration_;
};

class MoveServiceAction : public Action {
 public:
  MoveServiceAction(engineer_id_t eng_id, service_id_t service_id, binary_id_t bin_id) :
    eng_id_(eng_id),
    service_id_(service_id),
    bin_id_(bin_id) {}

  void apply(State& state) override;

 private:
  engineer_id_t eng_id_;
  service_id_t service_id_;
  binary_id_t bin_id_;
};

class AccumulateAction : public Action {
 public:
  AccumulateAction() = default;

  void addAction(std::unique_ptr<Action> action) {
    actions_.emplace_back(std::move(action));
  }

  void apply(State& state) override;

 private:
  std::vector<std::unique_ptr<Action>> actions_;
};

#endif