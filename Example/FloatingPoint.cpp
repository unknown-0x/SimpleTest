#include <SimpleTest/SimpleTest.hpp>

TEST_CASE(FP, Float) {
  const float a = 1.0F;
  const float b = 1.00000011920928955078125F;

  CHECK_NE(a, b);

  CHECK_FPEQ(a, b);
  CHECK_NEAR(a, b, std::numeric_limits<float>::epsilon());
}

TEST_CASE(FP, Double) {
  const double a = 1.0;
  const double b = 1.0000000000000002220446049250313080847263336181640625;

  CHECK_NE(a, b);

  CHECK_FPEQ(a, b);
  CHECK_NEAR(a, b, std::numeric_limits<double>::epsilon());
}