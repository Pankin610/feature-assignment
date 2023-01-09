#ifndef FIRST_TAKE_ACTION_PRODUCER_H
#define FIRST_TAKE_ACTION_PRODUCER_H

#include "state/state.h"
#include "state/action.h"
#include "action_producer_interface.h"

class FirstTakeActionProducer : public ActionProducerInterface {
 public:
  AccumulateAction<EngineerAction> getNextAction(State& state) override;

 private:
  std::unique_ptr<EngineerAction> takeFirstActionForEngineer(engineer_id_t id, State& state);
};

#endif