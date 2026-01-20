#include "TestSuite.hpp"

#include <algorithm>
#include <cassert>
#include <cstring>

namespace simpletest {
TestSuite::TestSuite(const char* name) : name_(name) {}

void TestSuite::RegisterTestCase(const char* test_case_name,
                                 TestCase::TestFunction func) {
  const auto pos =
      std::find_if(test_cases_.begin(), test_cases_.end(),
                   [&](const TestCase& test_case) -> bool {
                     return strcmp(test_case.GetName(), test_case_name) == 0;
                   });

  assert(pos == test_cases_.end());
  test_cases_.emplace_back(test_case_name, func);
}
}  // namespace simpletest