#include "TestCase.hpp"

#include <chrono>

namespace simpletest {
void TestCaseResult::AddFailureInfo(const char* file, int line) {
  if (failure_count_ == 0) {
    first_failure_index_ =
        static_cast<uint32_t>(GetGlobalFailureInfos().size());
  }
  GetGlobalFailureInfos().push_back({file, line});
  ++failure_count_;
}

std::vector<FailureInfo>& GetGlobalFailureInfos() {
  static std::vector<FailureInfo> failure_infos;
  return failure_infos;
}

TestCase::TestCase(const char* name, TestFunction func)
    : name_(name), func_(func) {}

TestCaseResult TestCase::Run() const {
  using MsDuration = std::chrono::duration<double, std::milli>;
  using ClockType = std::chrono::steady_clock;

  TestCaseResult result{};
  const auto start = ClockType::now();
  func_(result);
  result.elapsed_ = MsDuration{ClockType::now() - start}.count();
  return result;
}
}  // namespace simpletest
