#include <SimpleTest/SimpleTest.hpp>

TEST_CASE(Failed, Example01) {
  CHECK(0 == 1);
  CHECK(false);
}

TEST_CASE(Failed, Example02) {
  CHECK(false);
}