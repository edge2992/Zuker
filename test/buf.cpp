#include "gtest/gtest.h"
#include "zuker.h"

TEST(ZukerTest, EnergyTest){
  Zuker zuker("ATGC");
  ASSERT_EQ(4.6, zuker.eH(3, 7));
  ASSERT_EQ(INF, zuker.eH(3, 5));
  ASSERT_EQ(INF, zuker.eH(3, 34));
}

/* TEST(eStest, correctS){ */
/*   ASSERT_EQ(INF, eS(4,5)); */
/*   ASSERT_EQ(2.1, eS(4,11)); */
/*   ASSERT_EQ(INF, eS(4,35)); */
/* } */

/* TEST(eLtest, correctL){ */
/*   ASSERT_EQ(2.6, eL(4 ,20, 5, 10)); */
/*   ASSERT_EQ(1.0, eL(4,8, 5, 7)); */
/*   ASSERT_EQ(INF, eL(4,50, 10, 20)); */
/* } */

