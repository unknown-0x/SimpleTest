#include <SimpleTest/SimpleTest.hpp>

struct MathFixture {
  int a;
  int b;

  MathFixture() {
    a = 1;
    b = 2;
  }

  int add() const { return a + b; }
  int subtract() const { return a - b; }
  int multiply() const { return a * b; }
};

TEST_FIXTURE(MathFixture, InitMath) {
  CHECK_EQ(a, 1);
  CHECK_EQ(b, 2);
}

TEST_FIXTURE(MathFixture, MathFunctions) {
  CHECK_EQ(add(), 3);
  CHECK_EQ(subtract(), -1);
  CHECK_EQ(multiply(), 2);
}