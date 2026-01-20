#ifndef SIMPLE_TEST_TEST_RUNNER_HPP
#define SIMPLE_TEST_TEST_RUNNER_HPP

#include "TestSuite.hpp"

namespace simpletest {
class TestRunner {
 public:
  TestRunner() = default;
  TestRunner(TestRunner&&) = delete;
  TestRunner(const TestRunner&) = delete;
  TestRunner& operator=(TestRunner&&) = delete;
  TestRunner& operator=(const TestRunner&) = delete;

  ~TestRunner() = default;

  static TestRunner& Get();

  TestSuite& GetTestSuite(const char* name);
  int RunAllTests();

 private:
  void ProcessTestSuite(TestSuite& suite);
  void ProcessTestCaseResult(const TestCase& test_case);
  void PrintSummary() const;

  std::vector<TestSuite> test_suites_;
  double total_time_ = 0.0;
  int num_passed_ = 0;
  int num_failed_ = 0;
};
}  // namespace simpletest

#endif