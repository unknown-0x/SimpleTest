#ifndef SIMPLE_TEST_TEST_CASE_HPP
#define SIMPLE_TEST_TEST_CASE_HPP

#include <cstdint>
#include <vector>

namespace simpletest {
struct FailureInfo {
  const char* file;
  int line;
};

SIMPLETEST_API std::vector<FailureInfo>& GetGlobalFailureInfos();

class TestCase;

class SIMPLETEST_API TestCaseResult {
 public:
  friend class TestCase;

  void AddFailureInfo(const char* file, int line);

  bool IsPassed() const { return failure_count_ == 0; }
  double GetElapsed() const { return elapsed_; }

  template <typename Fn>
  void ForEachFailureInfo(Fn&& fn) const {
    if (failure_count_ == 0) {
      return;
    }
    const std::vector<FailureInfo>& infos = GetGlobalFailureInfos();
    for (uint32_t i = first_failure_index_, count = failure_count_; count > 0;
         ++i, --count) {
      fn(infos[i]);
    }
  }

 private:
  uint32_t first_failure_index_ = UINT32_MAX;
  uint32_t failure_count_ = 0;
  double elapsed_ = 0.0;
};

class SIMPLETEST_API TestCase {
 public:
  using TestFunction = void (*)(TestCaseResult&);

  TestCase(const char* name, TestFunction func);

  TestCaseResult Run() const;
  const char* GetName() const { return name_; }

 private:
  TestFunction func_;
  const char* name_;
};
}  // namespace simpletest

#endif