#ifndef SIMPLE_TEST_TEST_RUNNER_HPP
#define SIMPLE_TEST_TEST_RUNNER_HPP

#include "TestSuite.hpp"
#include "TestSummary.hpp"

namespace simpletest {
class Reporter;
class SIMPLETEST_API TestRunner {
 public:
  TestRunner(Reporter* reporter, const std::vector<TestSuite>& test_suites);

  TestRunner(TestRunner&&) = delete;
  TestRunner(const TestRunner&) = delete;
  TestRunner& operator=(TestRunner&&) = delete;
  TestRunner& operator=(const TestRunner&) = delete;

  int RunAllTests();

 private:
  void ProcessTestSuite(const TestSuite& suite);
  void ProcessTestCaseResult(const TestCaseResult& result);

  const std::vector<TestSuite>& test_suites_;
  TestSummary summary;
  Reporter* reporter_;
};
}  // namespace simpletest

#endif