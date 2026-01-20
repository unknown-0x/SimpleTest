#include <SimpleTest/SimpleTest.hpp>

TEST_CASE(Math, Add) {
  CHECK(1 + 1 == 2);
  CHECK(3 == 1 + 2);
}

TEST_CASE(Math, Comparision) {
  CHECK_EQ(1, 1);
  CHECK_NE(1, 2);

  CHECK_LT(1, 2);
  CHECK_LE(1, 2);
  CHECK_LE(1, 1);

  CHECK_GT(2, 1);
  CHECK_GE(2, 1);
  CHECK_GE(1, 1);
}