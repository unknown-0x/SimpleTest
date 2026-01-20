#ifndef SIMPLE_TEST_TEST_SUITE_HPP
#define SIMPLE_TEST_TEST_SUITE_HPP

#include "TestCase.hpp"

namespace simpletest {
class SIMPLETEST_API TestSuite {
 public:
  explicit TestSuite(const char* name);

  void RegisterTestCase(const char* test_case_name,
                        TestCase::TestFunction func);

  std::vector<TestCase>& GetTestCases() { return test_cases_; }
  const std::vector<TestCase>& GetTestCases() const { return test_cases_; }
  const char* GetName() const { return name_; }

 private:
  std::vector<TestCase> test_cases_;
  const char* name_;
};
}  // namespace simpletest

#endif