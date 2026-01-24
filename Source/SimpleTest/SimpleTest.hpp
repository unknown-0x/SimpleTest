#ifndef SIMPLE_TEST_SIMPLE_TEST_HPP
#define SIMPLE_TEST_SIMPLE_TEST_HPP

#include "TestMacros.hpp"
#include "TestRunner.hpp"
#include "UnitTest.hpp"

namespace simpletest {
SIMPLETEST_API int Main(int argc, char** argv);
}  // namespace simpletest

#define SIMPLE_TEST_MAIN()                 \
  int main(int argc, char** argv) {        \
    return ::simpletest::Main(argc, argv); \
  }

#endif