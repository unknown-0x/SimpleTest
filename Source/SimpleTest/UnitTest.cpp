#include "UnitTest.hpp"

#include "ConsoleReporter.hpp"
#include "TestRunner.hpp"

#include <algorithm>
#include <cstring>

namespace simpletest {
UnitTest::UnitTest() : reporter_(new ConsoleReporter{}) {}

UnitTest::~UnitTest() {
  SetReporter(nullptr);
}

int UnitTest::RunAllTests() {
  TestRunner runner{reporter_, test_suites_};
  return runner.RunAllTests();
}

void UnitTest::SetReporter(Reporter* new_reporter) {
  delete reporter_;
  reporter_ = new_reporter;
}

TestSuite& UnitTest::GetOrCreateTestSuite(const char* name) {
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

UnitTest& UnitTest::Get() {
  static UnitTest unit_test{};
  return unit_test;
}
}  // namespace simpletest
