#ifndef SIMPLE_TEST_SIMPLE_TEST_HPP
#define SIMPLE_TEST_SIMPLE_TEST_HPP

#include "TestCase.hpp"
#include "TestMacros.hpp"
#include "TestRunner.hpp"
#include "TestSuite.hpp"

namespace simpletest {
int Main(int argc, char** argv);
}  // namespace simpletest

#define SIMPLE_TEST_MAIN()                 \
  int main(int argc, char** argv) {        \
    return ::simpletest::Main(argc, argv); \
  }

#endif