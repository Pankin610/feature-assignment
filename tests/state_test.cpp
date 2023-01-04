#include <gtest/gtest.h>

#include "state.h"
#include "action.h"
#include <string>

TEST(StateTests, BasicTest) {
  State state(
    /*time_limit=*/100, 
    /*eng_count=*/10, 
    /*binary_count=*/10, 
    /*binary_creation_time=*/10);
  feature_id_t feature_id = state.featureMaintainer().addFeature("f", 5, 5);
  service_id_t service_id = state.serviceMaintainer().addByName("s");
  state.featureMaintainer().getFeature(feature_id).services().insert(service_id);
  state.binaryMaintainer().getBinary(0).services().insert(service_id);

  StartImplementingFeatureAction action(0, feature_id, 0);
  action.apply(state);
  state.advanceTime(3);
  EXPECT_EQ(state.score(), 0);
  state.advanceTime(10);
  EXPECT_EQ(state.score(), 5 * (100 - 5 - 1));
}

TEST(StateTests, TestFromStatement) {
  State state(
    /*time_limit=*/100, 
    /*eng_count=*/2, 
    /*binary_count=*/3, 
    /*binary_creation_time=*/10);
  feature_id_t foo_id = state.featureMaintainer().addFeature("foo", 1, 1);
  feature_id_t bar_id = state.featureMaintainer().addFeature("bar", 10, 1);
  Feature& foo = state.featureMaintainer().getFeature(foo_id);
  Feature& bar = state.featureMaintainer().getFeature(bar_id);

  service_id_t sa = state.serviceMaintainer().addByName("sa");
  service_id_t sb = state.serviceMaintainer().addByName("sb");
  service_id_t sc = state.serviceMaintainer().addByName("sc");
  service_id_t sd = state.serviceMaintainer().addByName("sd");
  service_id_t se = state.serviceMaintainer().addByName("se");

  state.binaryMaintainer().getBinary(0).services().insert(se);
  state.binaryMaintainer().getBinary(1).services().insert(sa);
  state.binaryMaintainer().getBinary(2).services().insert(sb);
  state.binaryMaintainer().getBinary(2).services().insert(sc);
  state.binaryMaintainer().getBinary(2).services().insert(sd);

  for (service_id_t service : state.binaryMaintainer().getBinary(2).services()) {
    foo.services().insert(service);
  }
  bar.services().insert(sa);
  bar.services().insert(sc);

  StartImplementingFeatureAction action1(
    /*eng_id=*/0, 
    /*feature_id=*/foo_id, 
    /*bin_id=*/2);
  StartImplementingFeatureAction action2(
    /*eng_id=*/1, 
    /*feature_id=*/bar_id, 
    /*bin_id=*/1);
  action1.apply(state);
  action2.apply(state);
  EXPECT_FALSE(state.engineerMaintainer().isAvailable(0));
  EXPECT_FALSE(state.engineerMaintainer().isAvailable(1));

  int time_for_foo = foo.difficulty() + state.binaryMaintainer().getBinary(2).services().size();
  state.advanceTime(time_for_foo);
  const auto& unimplemented_features = state.featureMaintainer().getUnimplementedFeatures();
  EXPECT_TRUE(unimplemented_features.find(foo_id) == unimplemented_features.end());
  int score_for_foo = (state.timeLimit() - time_for_foo) * foo.users();
  EXPECT_EQ(state.score(), score_for_foo);

  StartImplementingFeatureAction action3(
    /*eng_id=*/0,
    /*feature_id=*/bar_id,
    /*bin_id=*/2);
  action3.apply(state);

  int time_for_bar = std::max<int>(
    bar.difficulty() + 
      state.binaryMaintainer().getBinary(2).services().size() + 
      state.binaryMaintainer().numWorkersOnBinary(2),
    bar.difficulty() + 
      state.binaryMaintainer().getBinary(1).services().size() -
      state.curTime()
  );
  state.advanceTime(time_for_bar);
  EXPECT_TRUE(unimplemented_features.empty());

  int score_for_bar = (state.timeLimit() - state.curTime()) * bar.users();
  EXPECT_EQ(score_for_bar + score_for_foo, state.score());
  EXPECT_TRUE(state.engineerMaintainer().isAvailable(0));
  EXPECT_TRUE(state.engineerMaintainer().isAvailable(1));
}

TEST(StateTests, EngineerSleepTest) {
  State state(100, 10, 10, 10);
  EXPECT_TRUE(state.engineerMaintainer().isAvailable(0));

  EngineerSleepAction action(0, 5);
  action.apply(state);

  EXPECT_FALSE(state.engineerMaintainer().isAvailable(0));
}

