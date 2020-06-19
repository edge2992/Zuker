#include "gtest/gtest.h"
#include "zuker.h"

TEST(ZukerTest, EnergyTest){
  Zuker zuker("AUGC");
  ASSERT_EQ(4.6, zuker.eH(3, 7));
  ASSERT_EQ(INF, zuker.eH(3, 5));
  ASSERT_EQ(INF, zuker.eH(3, 34));

  ASSERT_EQ(INF, zuker.eS(4,5));
  ASSERT_EQ(2.1, zuker.eS(4,11));
  ASSERT_EQ(INF, zuker.eS(4,35));

  ASSERT_EQ(2.6, zuker.eL(4 ,20, 5, 10));
  ASSERT_EQ(1.0, zuker.eL(4,8, 5, 7));
  ASSERT_EQ(INF, zuker.eL(4,50, 10, 20));

}

