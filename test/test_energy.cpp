#include "gtest/gtest.h"
#include "energy.h"

TEST(eHtest, correctE){
  ASSERT_EQ(4.6, eH(3, 7));
  ASSERT_EQ(INF, eH(3, 5));
  ASSERT_EQ(INF, eH(3, 34));
}

