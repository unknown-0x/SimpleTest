#ifndef SIMPLE_TEST_INTERNAL_TEXT_BUFFER_HPP
#define SIMPLE_TEST_INTERNAL_TEXT_BUFFER_HPP

#include <cstring>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>

namespace simpletest {
namespace details {
template <typename T>
struct FloatFormatString;

template <>
struct FloatFormatString<float> {
  static constexpr const char* kFmt = "%.*f";
};

template <>
struct FloatFormatString<double> {
  static constexpr const char* kFmt = "%.*f";
};

template <>
struct FloatFormatString<long double> {
  static constexpr const char* kFmt = "%.*Lf";
};
}  // namespace details

class SIMPLETEST_API TextBuffer {
 public:
  struct Precision {
    int value;
  };

  explicit TextBuffer(std::size_t initial_capacity = 1024);

  void Clear();
  TextBuffer& operator<<(const char* s);
  TextBuffer& operator<<(char c);
  TextBuffer& operator<<(const std::string& s);
  TextBuffer& operator<<(std::string_view sv);
  TextBuffer& operator<<(const TextBuffer& value);

  template <typename Int>
  typename std::enable_if<std::is_integral<Int>::value, TextBuffer&>::type
  operator<<(const Int value) {
    AppendInt<Int>(value);
    return *this;
  }

  template <typename Float>
  typename std::enable_if<std::is_floating_point<Float>::value,
                          TextBuffer&>::type
  operator<<(const Float value) {
    AppendFloat<Float>(value);
    return *this;
  }

  Precision SetPrecision(int precision);
  TextBuffer& operator<<(const Precision precision);

  friend std::ostream& operator<<(std::ostream& output,
                                  const TextBuffer& buffer) {
    output.write(buffer.buffer_.data(), buffer.buffer_.size());
    return output;
  }

 private:
  template <typename Int>
  void AppendInt(const Int value) {
    static_assert(std::is_integral<Int>::value,
                  "Template type must be an integral type.");

    if (value == 0) {
      buffer_ += '0';
      return;
    }

    char buffer[24];
    char* end = buffer + sizeof(buffer);
    char* ptr = end - 1;
    *ptr = '\0';

    using UnsignedInt = typename std::make_unsigned<Int>::type;
    bool is_negative = false;
    UnsignedInt unsigned_value = 0;

    if constexpr (std::is_signed<Int>::value) {
      if (value < 0) {
        is_negative = true;
        unsigned_value = static_cast<UnsignedInt>(-(value + 1)) + 1;
      } else {
        unsigned_value = static_cast<UnsignedInt>(value);
      }
    } else {
      unsigned_value = value;
    }

    while (unsigned_value > 0) {
      *--ptr = (char)('0' + (unsigned_value % 10));
      unsigned_value /= 10;
    }

    if (is_negative) {
      *--ptr = '-';
    }

    buffer_.append(ptr, end - ptr);
  }

  template <typename Float>
  void AppendFloat(const Float value) {
    static_assert(std::is_floating_point<Float>::value,
                  "Template type must be an floating-point type.");
    static constexpr int kBufferSize =
        std::numeric_limits<Float>::max_exponent10 + 20;
    char buffer[kBufferSize];
    int written = std::snprintf(buffer, kBufferSize,
                                details::FloatFormatString<Float>::kFmt,
                                precision_.value, value);
    buffer_.append(buffer, written);
  }

  TextBuffer& Append(const char* s, size_t count);

  std::string buffer_;
  Precision precision_{4};
};
}  // namespace simpletest

#endif