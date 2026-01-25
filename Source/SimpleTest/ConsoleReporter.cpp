#include "ConsoleReporter.hpp"

#include <iomanip>
#include <iostream>
#include "Style.hpp"

namespace simpletest {
ConsoleReporter::ConsoleReporter() {
  RefreshStream(std::cout);
}

void ConsoleReporter::ReportTestSuiteStart(const TestSuite& test_suite) {
  const auto& test_cases = test_suite.GetTestCases();
  const char* suite_name = test_suite.GetName();
  const auto num_test_cases = static_cast<int>(test_cases.size());
  const char* const test_case_text =
      (num_test_cases == 1) ? "test case" : "test cases";

  TextBuffer buffer{256};
  buffer << (Style::kBold | Style::kFgWhite) << "==========" << ' '
         << suite_name << " (" << num_test_cases << ' ' << test_case_text << ')'
         << Style::kReset << "\n"
         << "----------\n";
  std::cout << buffer;
}

void ConsoleReporter::ReportTestCaseStart(const TestCase& /*test_case*/) {}

void ConsoleReporter::ReportTestCaseFinish(const TestCase& test_case,
                                           const TestCaseResult& result) {
  const bool is_passed = result.IsPassed();
  const double elapsed_ms = result.GetElapsed();
  const char* test_status = is_passed ? "Passed" : "Failed";
  const Style test_status_color = is_passed ? Style::kBgGreen : Style::kBgRed;

  TextBuffer buffer{};
  buffer << '[' << (test_status_color | Style::kBold) << " " << test_status
         << " " << Style::kReset << "] " << test_case.GetName() << " ("
         << buffer.SetPrecision(3) << elapsed_ms << " ms)\n";
  if (!is_passed) {
    result.ForEachFailureInfo([&](const FailureInfo& info) {
      buffer << "- Test " << Style::kFgRed << "failed" << Style::kReset
             << " at " << Style::kFgBlue << info.file << ':' << info.line
             << Style::kReset << '\n';
    });
  }
  buffer << "----------\n";
  std::cout << buffer;
}

void ConsoleReporter::ReportTestSuiteFinish(const TestSuite& /*test_suite*/) {
  std::cout.write("\n", 1);
}

void ConsoleReporter::ReportSummary(const TestSummary& summary) {
  const auto total_test_cases =
      summary.passed_test_cases + summary.failed_test_cases;

  const double pass_percentage =
      total_test_cases == 0
          ? 100  // NOLINT
          : static_cast<int>(static_cast<float>(summary.passed_test_cases) /
                             static_cast<float>(total_test_cases) * 100.F);

  TextBuffer buffer{};
  buffer << (Style::kBold | Style::kFgWhite) << "=================== ";
  buffer << (Style::kBold | Style::kFgBlue) << "Test summary";
  buffer << (Style::kBold | Style::kFgWhite) << " ===================\n";
  buffer << Style::kReset;

  buffer << ">> Result: " << pass_percentage << "% tests passed\n";
  buffer << ">> Passed: " << Style::kFgGreen << summary.passed_test_cases
         << Style::kReset
         << (summary.passed_test_cases == 1 ? " test case" : " test cases")
         << '\n';
  buffer << ">> Failed: " << Style::kFgRed << summary.failed_test_cases
         << Style::kReset
         << (summary.failed_test_cases == 1 ? " test case" : " test cases")
         << '\n';
  buffer << ">> Time  : " << buffer.SetPrecision(3) << summary.total_time_ms
         << " ms\n";

  buffer << (Style::kBold | Style::kFgWhite)
         << "====================================================\n"
         << Style::kReset;
  std::cout << buffer;
}
}  // namespace simpletest