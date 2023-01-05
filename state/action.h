#ifndef ACTION_H
#define ACTION_H

#include "state.h"
#include "feature.h"
#include "types.h"
#include "problem_data.h"
#include <memory>

class State;

class Action {
 public:
  virtual void apply(State& state) = 0;
  virtual ~Action() {}
};

class EngineerAction : public Action {
 public:
  EngineerAction(engineer_id_t eng_id) :
    eng_id_(eng_id) {}

  engineer_id_t getEngId() const {
    return eng_id_;
  }

  virtual std::string toString() const = 0;
  virtual ~EngineerAction() {}

 protected:
  engineer_id_t eng_id_;
};

class ImplementFeatureAction : public Action {
 public:
  ImplementFeatureAction(feature_id_t feature_id, binary_id_t bin_id, int time_done) :
    feature_id_(feature_id),
    bin_id_(bin_id),
    time_done_(time_done) {}
    
  void apply(State& state) override;

 private:
  feature_id_t feature_id_;
  binary_id_t bin_id_;
  int time_done_;
};

class StartImplementingFeatureAction : public EngineerAction {
 public:
  StartImplementingFeatureAction(
    engineer_id_t eng_id, 
    feature_id_t feature_id, 
    binary_id_t bin_id, 
    std::shared_ptr<ProblemData> data
  ) : EngineerAction(eng_id),
      feature_id_(feature_id),
      bin_id_(bin_id),
      data_(std::move(data)) {}
    
  void apply(State& state) override;
  std::string toString() const override;

  ~StartImplementingFeatureAction() {}

 private:
  feature_id_t feature_id_;
  binary_id_t bin_id_;
  std::shared_ptr<ProblemData> data_;
};

class EngineerSleepAction : public EngineerAction {
 public:
  EngineerSleepAction(engineer_id_t eng_id, int duration = 1) :
    EngineerAction(eng_id),
    duration_(duration) {}

  void apply(State& state) override;
  std::string toString() const override;

  ~EngineerSleepAction() {}

 private:
  int duration_;
};

class MoveServiceAction : public EngineerAction {
 public:
  MoveServiceAction(
    engineer_id_t eng_id, 
    service_id_t service_id, 
    binary_id_t bin_id,
    std::shared_ptr<ProblemData> data
  ) : EngineerAction(eng_id),
      service_id_(service_id),
      bin_id_(bin_id),
      data_(std::move(data)) {}

  void apply(State& state) override;
  std::string toString() const override;

 private:
  service_id_t service_id_;
  binary_id_t bin_id_;
  std::shared_ptr<ProblemData> data_;
};

class CreateBinaryAction : public EngineerAction {
 public:
  CreateBinaryAction(engineer_id_t eng_id) : EngineerAction(eng_id) {}

  void apply(State& state) override;
  std::string toString() const override;
};

template<typename ActionType>
class AccumulateAction : public Action {
 public:
  AccumulateAction() = default;

  void addAction(std::unique_ptr<ActionType> action) {
    actions_.emplace_back(std::move(action));
  }

  void apply(State& state) override {
    for (const auto& action : actions_) {
      action->apply(state);
    }
  }

  std::vector<std::unique_ptr<ActionType>>& actions() {
    return actions_;
  }

 private:
  std::vector<std::unique_ptr<ActionType>> actions_;
};

#endif