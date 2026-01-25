#ifndef SIMPLE_TEST_INTERNAL_STYLES_HPP
#define SIMPLE_TEST_INTERNAL_STYLES_HPP

#include <ostream>
#include <type_traits>

#include "TextBuffer.hpp"

namespace simpletest {

#define BIT(x) (1 << x)

enum class Style {
  kReset = BIT(1),
  kBold = BIT(2),
  kFgWhite = BIT(3),
  kFgRed = BIT(4),
  kFgGreen = BIT(5),
  kFgYellow = BIT(6),
  kFgBlue = BIT(7),
  kBgRed = BIT(8),
  kBgGreen = BIT(9),
};

constexpr Style operator|(Style lhs, Style rhs) noexcept {
  using U = std::underlying_type_t<Style>;
  return static_cast<Style>(static_cast<U>(lhs) | static_cast<U>(rhs));
}

constexpr Style operator&(Style lhs, Style rhs) noexcept {
  using U = std::underlying_type_t<Style>;
  return static_cast<Style>(static_cast<U>(lhs) & static_cast<U>(rhs));
}

constexpr bool HasStyle(Style style, Style s) noexcept {
  return static_cast<int>(style & s) != 0;
}

SIMPLETEST_API void RefreshStream(std::ostream& output);
}  // namespace simpletest

SIMPLETEST_API simpletest::TextBuffer& operator<<(
    simpletest::TextBuffer& output,
    const simpletest::Style style);

#endif