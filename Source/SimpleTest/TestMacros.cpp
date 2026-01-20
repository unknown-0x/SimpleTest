#include "TestMacros.hpp"

#include "TestRunner.hpp"

#include <cmath>
#include <cstring>

namespace simpletest {
bool CreateTestCase(const char* suite,
                    const char* name,
                    TestCase::TestFunction fn) {
  TestRunner::Get().GetTestSuite(suite).RegisterTestCase(name, fn);
  return true;
}

void ExpectImpl(TestCaseResult& result,
                bool value,
                const char* file,
                int line) {
  if (!value) {
    result.AddFailureInfo(file, line);
  }
}

bool CompareStr(std::string_view lhs, std::string_view rhs) {
  return lhs == rhs;
}

bool CompareStr(std::wstring_view lhs, std::wstring_view rhs) {
  return lhs == rhs;
}

#ifdef __cpp_char8_t
bool CompareStr(std::u8string_view lhs, std::u8string_view rhs) {
  return lhs == rhs;
}
#endif

bool CompareStr(std::u16string_view lhs, std::u16string_view rhs) {
  return lhs == rhs;
}

bool CompareStr(std::u32string_view lhs, std::u32string_view rhs) {
  return lhs == rhs;
}

template <typename U>
struct ChooseUIntType;

template <>
struct ChooseUIntType<float> {
  using Type = unsigned int;
};

template <>
struct ChooseUIntType<double> {
  using Type = unsigned long long;
};

template <typename T>
class FloatComparator {
 public:
  using UInt = typename ChooseUIntType<T>::Type;

  static constexpr UInt kMaxUlps = 4;
  static constexpr UInt kBitCount = 8 * sizeof(T);
  static constexpr UInt kSignBitMask = static_cast<UInt>(1) << (kBitCount - 1);

  static UInt FloatToBits(T x) {
    UInt bits;
    std::memcpy(&bits, &x, sizeof(bits));
    return bits;
  }

  static UInt SignMagnitude(UInt bits) {
    return (kSignBitMask & bits) ? (~bits + 1) : (kSignBitMask | bits);
  }

  static UInt UlpDistance(UInt lhs_bits, UInt rhs_bits) {
    const UInt lhs_mag = SignMagnitude(lhs_bits);
    const UInt rhs_mag = SignMagnitude(rhs_bits);
    return (lhs_mag >= rhs_mag) ? (lhs_mag - rhs_mag) : (rhs_mag - lhs_mag);
  }

  FloatComparator(T lhs, T rhs) : lhs_(lhs), rhs_(rhs) {}

  bool operator()() {
    if (std::isnan(lhs_) || std::isnan(rhs_)) {
      return false;
    }
    const UInt lhs_bits = FloatToBits(lhs_);
    const UInt rhs_bits = FloatToBits(rhs_);
    return UlpDistance(lhs_bits, rhs_bits) <= kMaxUlps;
  }

 private:
  T lhs_;
  T rhs_;
};

bool CompareFP(float lhs, float rhs) {
  return FloatComparator<float>{lhs, rhs}();
}
bool CompareFP(double lhs, double rhs) {
  return FloatComparator<double>{lhs, rhs}();
}

bool AreAlmostEqual(float lhs, float rhs, float epsilon) {
  return std::abs(lhs - rhs) <= epsilon;
}

bool AreAlmostEqual(double lhs, double rhs, double epsilon) {
  return std::abs(lhs - rhs) <= epsilon;
}
}  // namespace simpletest
