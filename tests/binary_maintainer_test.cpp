#include <gtest/gtest.h>

#include "state/binary_maintainer.h"

TEST(BinaryMaintainerTests, BasicTest) {
  BinaryMaintainer maintainer(/*n=*/5);
  EXPECT_EQ(maintainer.getAvailableBinaries().size(), 5);
  
  maintainer.blockBinary(/*id=*/0, /*duration=*/5);
  EXPECT_EQ(maintainer.getAvailableBinaries().size(), 4);

  maintainer.advanceTime(5);
  EXPECT_EQ(maintainer.getAvailableBinaries().size(), 5);
}


TEST(BinaryMaintainerTests, ThrowsWhenCannotBlockTest) {
  BinaryMaintainer maintainer(/*n=*/5);
  maintainer.workOnBinary(/*id=*/0);
  maintainer.advanceTime(2);

  EXPECT_THROW(maintainer.blockBinary(0, 3), std::runtime_error);
}
