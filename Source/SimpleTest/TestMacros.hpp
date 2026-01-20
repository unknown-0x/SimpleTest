#ifndef SIMPLE_TEST_TEST_MACROS_HPP
#define SIMPLE_TEST_TEST_MACROS_HPP

#include "TestCase.hpp"

#include <cmath>
#include <limits>
#include <string_view>

namespace simpletest {
bool CreateTestCase(const char* suite,
                    const char* name,
                    TestCase::TestFunction fn);

void ExpectImpl(TestCaseResult& result, bool value, const char* file, int line);

bool CompareStr(std::string_view lhs, std::string_view rhs);
bool CompareStr(std::wstring_view lhs, std::wstring_view rhs);
#ifdef __cpp_char8_t
bool CompareStr(std::u8string_view lhs, std::u8string_view rhs);
#endif
bool CompareStr(std::u16string_view lhs, std::u16string_view rhs);
bool CompareStr(std::u32string_view lhs, std::u32string_view rhs);

bool CompareFP(float lhs, float rhs);
bool CompareFP(double lhs, double rhs);

bool AreAlmostEqual(float lhs,
                    float rhs,
                    float epsilon = std::numeric_limits<float>::epsilon());
bool AreAlmostEqual(double lhs,
                    double rhs,
                    double epsilon = std::numeric_limits<double>::epsilon());
}  // namespace simpletest

#define SIMPLE_TEST_RESULT_PARAM result
#define SIMPLE_TEST_UNUSED_RESULT() (void)SIMPLE_TEST_RESULT_PARAM

#define TEST_CASE_IMPL(suite, test_case)                                     \
  void Test##suite##test_case(::simpletest::TestCaseResult&);                \
  static const bool __##suite##test_case##__ = ::simpletest::CreateTestCase( \
      #suite, #test_case, Test##suite##test_case);                           \
  void Test##suite##test_case(                                               \
      ::simpletest::TestCaseResult& SIMPLE_TEST_RESULT_PARAM)

#define TEST_CASE(suite, test_case) TEST_CASE_IMPL(suite, test_case)

#define CHECK(...)                                                            \
  ::simpletest::ExpectImpl(SIMPLE_TEST_RESULT_PARAM, (__VA_ARGS__), __FILE__, \
                           __LINE__)

#define CHECK_EQ(lhs, rhs) CHECK(lhs == rhs)
#define CHECK_NE(lhs, rhs) CHECK(lhs != rhs)

#define CHECK_LT(lhs, rhs) CHECK(lhs < rhs)
#define CHECK_LE(lhs, rhs) CHECK(lhs <= rhs)

#define CHECK_GT(lhs, rhs) CHECK(lhs > rhs)
#define CHECK_GE(lhs, rhs) CHECK(lhs >= rhs)

#define CHECK_STREQ(lhs, rhs) CHECK(::simpletest::CompareStr(lhs, rhs))
#define CHECK_STRNE(lhs, rhs) CHECK(!::simpletest::CompareStr(lhs, rhs))

#define CHECK_FPEQ(lhs, rhs) CHECK(::simpletest::CompareFP(lhs, rhs))
#define CHECK_NEAR(lhs, rhs, epsilon) \
  CHECK(::simpletest::AreAlmostEqual(lhs, rhs, epsilon))

#endif