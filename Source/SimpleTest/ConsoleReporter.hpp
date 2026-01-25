#ifndef SIMPLE_TEST_CONSOLE_REPORTER_HPP
#define SIMPLE_TEST_CONSOLE_REPORTER_HPP

#include "Reporter.hpp"

namespace simpletest {
class SIMPLETEST_API ConsoleReporter : public Reporter {
 public:
  ConsoleReporter();
  void ReportTestSuiteStart(const TestSuite& test_suite) override;
  void ReportTestCaseStart(const TestCase& test_case) override;
  void ReportTestCaseFinish(const TestCase& test_case,
                            const TestCaseResult&) override;
  void ReportTestSuiteFinish(const TestSuite& test_suite) override;
  void ReportSummary(const TestSummary& summary) override;
};
}  // namespace simpletest

#endif