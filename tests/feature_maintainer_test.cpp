#include <gtest/gtest.h>

#include "feature_maintainer.h"

TEST(FeatureMaintainerTests, BasicTest) {
  FeatureMaintainer maintainer;
  maintainer.addFeature("useless feature", 1, 0);
  maintainer.addFeature("useful feature", 10, 100000);
  
  auto unimplemented = maintainer.getUnimplementedFeatures();
  EXPECT_TRUE(unimplemented.find(0) != unimplemented.end());
  EXPECT_TRUE(unimplemented.find(1) != unimplemented.end());

  maintainer.implement(0);
  unimplemented = maintainer.getUnimplementedFeatures();
  EXPECT_TRUE(unimplemented.find(0) == unimplemented.end());
  EXPECT_TRUE(unimplemented.find(1) != unimplemented.end());
}

