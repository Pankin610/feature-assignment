#ifndef ACTION_PRODUCER_H
#define ACTION_PRODUCER_H

#include "action.h"
#include "state.h"

class ActionProducerInterface {
 public:
  virtual AccumulateAction<EngineerAction> getNextAction(State& state) = 0;
  virtual ~ActionProducerInterface() {}
};

#endif