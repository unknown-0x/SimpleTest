#include "ConsoleReporter.hpp"

#include <iomanip>
#include <iostream>
#include "Internal/Style.hpp"

namespace simpletest {
void ConsoleReporter::ReportTestSuiteStart(const TestSuite& test_suite) {
  const auto& test_cases = test_suite.GetTestCases();
  const char* suite_name = test_suite.GetName();
  const auto num_test_cases = static_cast<int>(test_cases.size());
  const char* const test_case_text =
      (num_test_cases == 1) ? "test case" : "test cases";

  std::cout << (Style::kBold | Style::kFgWhite) << "==========" << ' '
            << suite_name << " (" << num_test_cases << ' ' << test_case_text
            << ')' << Style::kReset << "\n";
  std::cout << "----------\n";
}

void ConsoleReporter::ReportTestCaseStart(const TestCase& /*test_case*/) {}

void ConsoleReporter::ReportTestCaseFinish(const TestCase& test_case,
                                           const TestCaseResult& result) {
  const bool is_passed = result.IsPassed();
  const double elapsed_ms = result.GetElapsed();
  const char* test_status = is_passed ? "Passed" : "Failed";
  const Style test_status_color = is_passed ? Style::kBgGreen : Style::kBgRed;
  std::cout << '[' << (test_status_color | Style::kBold) << " " << test_status
            << " " << Style::kReset << "] " << test_case.GetName() << " ("
            << std::setprecision(4) << elapsed_ms << " ms)\n";
  if (!is_passed) {
    result.ForEachFailureInfo([](const FailureInfo& info) {
      std::cout << "- Test " << Style::kFgRed << "failed" << Style::kReset
                << " at " << Style::kFgBlue << info.file << ':' << info.line
                << Style::kReset << '\n';
    });
  }
  std::cout << "----------\n";
}

void ConsoleReporter::ReportTestSuiteFinish(const TestSuite& /*test_suite*/) {
  std::cout << '\n';
}

void ConsoleReporter::ReportSummary(const TestSummary& summary) {
  const auto total_test_cases =
      summary.passed_test_cases + summary.failed_test_cases;

  const double pass_percentage =
      total_test_cases == 0
          ? 100  // NOLINT
          : static_cast<int>(static_cast<float>(summary.passed_test_cases) /
                             static_cast<float>(total_test_cases) * 100.F);

  std::cout << (Style::kBold | Style::kFgWhite) << "=================== ";
  std::cout << (Style::kBold | Style::kFgBlue) << "Test summary";
  std::cout << (Style::kBold | Style::kFgWhite) << " ===================\n";
  std::cout << Style::kReset;

  std::cout << ">> Result: " << pass_percentage << "% tests passed\n";
  std::cout << ">> Passed: " << Style::kFgGreen << summary.passed_test_cases
            << Style::kReset
            << (summary.passed_test_cases == 1 ? " test case" : " test cases")
            << '\n';
  std::cout << ">> Failed: " << Style::kFgRed << summary.failed_test_cases
            << Style::kReset
            << (summary.failed_test_cases == 1 ? " test case" : " test cases")
            << '\n';
  std::cout << ">> Time  : " << std::setprecision(4) << summary.total_time_ms
            << " ms\n";

  std::cout << (Style::kBold | Style::kFgWhite)
            << "====================================================\n"
            << Style::kReset;
}
}  // namespace simpletest