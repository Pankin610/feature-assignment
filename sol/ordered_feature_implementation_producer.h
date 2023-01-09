#ifndef ORDERED_FEATURE_IMPLEMENTATION_PRODUCER_H
#define ORDERED_FEATURE_IMPLEMENTATION_PRODUCER_H

#include "state/state.h"
#include "state/action.h"
#include "action_producer_interface.h"

class OrderedFeatureImplementationProducer : public ActionProducerInterface {
 public:
  OrderedFeatureImplementationProducer(const ProblemData& data);
  
  AccumulateAction<EngineerAction> getNextAction(State& state) override;

 private:
  std::unique_ptr<EngineerAction> takeFirstActionInOrder(engineer_id_t id, State& state);
  
  std::vector<feature_id_t> feature_order_;
};

#endif