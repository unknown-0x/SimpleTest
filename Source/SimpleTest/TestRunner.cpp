#include "TestRunner.hpp"

#include <algorithm>
#include <cstdio>
#include <cstring>

namespace simpletest {
namespace {
// https://github.com/agauniyal/rang/blob/22345aa4c468db3bd4a0e64a47722aad3518cc81/include/rang.hpp#L139
// https://github.com/gabime/spdlog/blob/8806ca6509f037cf7612ea292338e3b222209dc1/include/spdlog/details/os-inl.h#L401
bool SupportsColor() noexcept {
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
  return true;
#elif defined(__unix__) || defined(__unix) || defined(__linux__) || \
    defined(__APPLE__) || defined(__MACH__)
  const char* envTERM = std::getenv("TERM");
  const char* envCOLORTERM = std::getenv("COLORTERM");
  if (envTERM || envCOLORTERM) {
    return true;
  }

  static constexpr std::array<const char*, 16> kTerms = {
      {"ansi", "color", "console", "cygwin", "gnome", "konsole", "kterm",
       "linux", "msys", "putty", "rxvt", "screen", "vt100", "xterm",
       "alacritty", "vt102"}};

  return std::any_of(kTerms.begin(), kTerms.end(), [&](const char* term) {
    return std::strstr(envTERM, term) != nullptr;
  });
#endif
}

const bool kSupportsColor = SupportsColor();

const char* MakeStyle(const char* value) {
  return kSupportsColor ? value : "";
}

const char* const kBgGreen = MakeStyle("\033[42m");
const char* const kBgRed = MakeStyle("\033[41m");

const char* const kBold = MakeStyle("\033[1m");

const char* const kReset = MakeStyle("\033[m");
const char* const kDark = MakeStyle("\033[2m");
const char* const kRed = MakeStyle("\033[31m");
const char* const kBlue = MakeStyle("\033[94m");

const char* const kRedBold = MakeStyle(
    "\033[31m"
    "\033[1m");
const char* const kGreenBold = MakeStyle(
    "\033[32m"
    "\033[1m");
const char* const kWhiteBold = MakeStyle(
    "\033[37m"
    "\033[1m");
const char* const kBlueBold = MakeStyle(
    "\033[94m"
    "\033[1m");

}  // namespace

TestRunner& TestRunner::Get() {
  static TestRunner runner{};
  return runner;
}

TestSuite& TestRunner::GetTestSuite(const char* name) {
  const auto pos = std::find_if(test_suites_.begin(), test_suites_.end(),
                                [&](const TestSuite& suite) -> bool {
                                  return strcmp(suite.GetName(), name) == 0;
                                });
  if (pos != test_suites_.end()) {
    return *pos;
  }
  test_suites_.emplace_back(name);
  return test_suites_.back();
}

int TestRunner::RunAllTests() {
  for (auto& suite : test_suites_) {
    ProcessTestSuite(suite);
  }
  PrintSummary();

  return num_failed_ == 0 ? 0 : 1;
}

void TestRunner::ProcessTestSuite(TestSuite& suite) {
  auto& test_cases = suite.GetTestCases();
  const char* suite_name = suite.GetName();
  const auto num_cases = static_cast<int>(test_cases.size());

  const char* const test_case_text =
      (num_cases == 1) ? "test case" : "test cases";
  printf(
      "%s==============%s\n"
      "%s[ Test suite ] %s (%d %s)%s\n"
      "%s==============%s\n",
      kWhiteBold, kReset, kWhiteBold, suite_name, num_cases, test_case_text,
      kReset, kWhiteBold, kReset);

  for (auto& test_case : test_cases) {
    test_case.Run();
    ProcessTestCaseResult(test_case);
  }
  printf("\n");
}

void TestRunner::ProcessTestCaseResult(const TestCase& test_case) {  // NOLINT
  const TestCaseResult& result = test_case.GetResult();
  const bool is_passed = result.IsPassed();
  const char* const test_status = is_passed ? "Passed" : "Failed";
  const char* const test_status_color = is_passed ? kBgGreen : kBgRed;
  const double elapsed = result.GetElapsed();
  total_time_ += elapsed;
  printf("[%s%s   %s   %s] %s (%.3lf ms)\n", test_status_color, kBold,
         test_status, kReset, test_case.GetName(), elapsed);
  if (!is_passed) {
    ++num_failed_;
    test_case.ProcessFailureInfos([](const FailureInfo& info) {
      printf(" - Test %sfailed%s at %s%s:%d%s\n", kRed, kReset, kBlue,
             info.file, info.line, kReset);
    });
  } else {
    ++num_passed_;
  }
  printf("--------------\n");
}

void TestRunner::PrintSummary() const {
  const auto total_test_cases = num_passed_ + num_failed_;
  printf("%s===================%s %sTest summary%s %s===================%s\n",
         kWhiteBold, kReset, kBlueBold, kReset, kWhiteBold, kReset);
  printf(">> Result: %s%d%% tests passed%s\n", kGreenBold,
         total_test_cases == 0
             ? 100  // NOLINT
             : static_cast<int>(static_cast<float>(num_passed_) /
                                static_cast<float>(total_test_cases) * 100.F),
         kReset);
  printf(">> Passed: %s%d%s %s\n", kGreenBold, num_passed_, kReset,
         (num_passed_ == 1) ? "test case" : "test cases");
  printf(">> Failed: %s%d%s %s\n", kRedBold, num_failed_, kReset,
         (num_failed_ == 1) ? "test case" : "test cases");
  printf(">> Time  : %.3lf ms\n", total_time_);
  printf("%s====================================================%s\n",
         kWhiteBold, kReset);
}
}  // namespace simpletest
