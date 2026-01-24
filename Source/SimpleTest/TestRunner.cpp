#include "TestRunner.hpp"
#include "Reporter.hpp"

#include <algorithm>
#include <cstdio>
#include <cstring>

namespace simpletest {
TestRunner::TestRunner(Reporter* reporter,
                       const std::vector<TestSuite>& test_suites)
    : test_suites_(test_suites), reporter_(reporter), summary{} {}

int TestRunner::RunAllTests() {
  for (const auto& suite : test_suites_) {
    reporter_->ReportTestSuiteStart(suite);
    ProcessTestSuite(suite);
    reporter_->ReportTestSuiteFinish(suite);
  }
  reporter_->ReportSummary(summary);
  return summary.failed_test_cases == 0 ? 0 : 1;
}

void TestRunner::ProcessTestSuite(const TestSuite& suite) {
  const auto& test_cases = suite.GetTestCases();
  for (const auto& test_case : test_cases) {
    reporter_->ReportTestCaseStart(test_case);
    const TestCaseResult result = test_case.Run();
    ProcessTestCaseResult(result);
    reporter_->ReportTestCaseFinish(test_case, result);
  }
}

void TestRunner::ProcessTestCaseResult(const TestCaseResult& result) {
  const bool is_passed = result.IsPassed();
  summary.total_time_ms += result.GetElapsed();
  if (!is_passed) {
    ++summary.failed_test_cases;
  } else {
    ++summary.passed_test_cases;
  }
}
}  // namespace simpletest
