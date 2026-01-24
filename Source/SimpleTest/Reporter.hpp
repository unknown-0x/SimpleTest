#ifndef SIMPLE_TEST_REPORTER_HPP
#define SIMPLE_TEST_REPORTER_HPP

#include "TestSuite.hpp"
#include "TestSummary.hpp"

namespace simpletest {
class Reporter {
 public:
  virtual ~Reporter() = default;

  virtual void ReportTestSuiteStart(const TestSuite&) = 0;
  virtual void ReportTestCaseStart(const TestCase&) = 0;
  virtual void ReportTestCaseFinish(const TestCase&, const TestCaseResult&) = 0;
  virtual void ReportTestSuiteFinish(const TestSuite&) = 0;
  virtual void ReportSummary(const TestSummary&) = 0;
};
}  // namespace simpletest

#endif