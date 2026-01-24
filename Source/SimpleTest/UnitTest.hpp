#ifndef SIMPLE_TEST_UNIT_TEST_HPP
#define SIMPLE_TEST_UNIT_TEST_HPP

#include "TestSuite.hpp"

namespace simpletest {
class Reporter;

class SIMPLETEST_API UnitTest {
 public:
  UnitTest();
  UnitTest(UnitTest&&) = delete;
  UnitTest(const UnitTest&) = delete;
  UnitTest& operator=(UnitTest&&) = delete;
  UnitTest& operator=(const UnitTest&) = delete;
  ~UnitTest();

  int RunAllTests();
  void SetReporter(Reporter* new_reporter);
  TestSuite& GetOrCreateTestSuite(const char* name);

  static UnitTest& Get();

 private:
  std::vector<TestSuite> test_suites_;
  Reporter* reporter_ = nullptr;
};
}  // namespace simpletest

#endif