#ifndef SIMPLE_TEST_TEST_SUMMARY_HPP
#define SIMPLE_TEST_TEST_SUMMARY_HPP

namespace simpletest {
struct TestSummary {
  int passed_test_cases;
  int failed_test_cases;
  double total_time_ms;
};
}  // namespace simpletest

#endif