#include "Style.hpp"

#include <array>
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
#define OS_WINDOWS
#elif defined(__unix__) || defined(__unix) || defined(__linux__)
#define OS_LINUX
#elif defined(__APPLE__) || defined(__MACH__)
#define OS_MAC
#endif

#if defined(OS_WINDOWS)
#include <io.h>
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#define FILENO(file) _fileno(file)
#endif

#if defined(OS_LINUX) || defined(OS_MAC)
#include <unistd.h>
#include <algorithm>
#include <cstring>
#define FILENO(file) fileno(file)
#endif

namespace simpletest {
// NOLINTBEGIN
namespace {
bool SupportsColorImpl() noexcept {
  // https://github.com/agauniyal/rang/blob/22345aa4c468db3bd4a0e64a47722aad3518cc81/include/rang.hpp#L139
  // https://github.com/gabime/spdlog/blob/8806ca6509f037cf7612ea292338e3b222209dc1/include/spdlog/details/os-inl.h#L401
#if defined(OS_WINDOWS)
  return true;
#elif defined(OS_LINUX) || defined(OS_MAC)
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

#if defined(OS_WINDOWS)
HANDLE GetHANDLE(FILE* file) {
  const int fd = FILENO(file);
  return reinterpret_cast<HANDLE>(_get_osfhandle(fd));
}
#endif

bool IsTerminalImpl(FILE* file) noexcept {
  if (!file) {
    return false;
  }

#if defined(OS_WINDOWS)
  auto handle = GetHANDLE(file);
  if (handle == INVALID_HANDLE_VALUE) {
    return false;
  }

  if (GetFileType(handle) != FILE_TYPE_PIPE) {
    return false;
  }

  DWORD mode = 0;
  if (GetConsoleMode(handle, &mode)) {
    return true;
  }

  WCHAR path[MAX_PATH];
  DWORD size =
      GetFinalPathNameByHandleW(handle, path, MAX_PATH, FILE_NAME_NORMALIZED);

  if (size > 0 && size < MAX_PATH) {
    std::wstring name(path, static_cast<size_t>(size));
    if ((name.find(L"msys-") == std::string::npos &&
         name.find(L"cygwin-") == std::string::npos) ||
        name.find(L"-pty") == std::string::npos) {
      return false;
    }
  }

  return false;
#elif defined(OS_LINUX) || defined(OS_MAC)
  return ::isatty(fileno(file)) != 0;
#endif
}

bool SupportsColor() noexcept {
  static const bool kSupportsColor = SupportsColorImpl();
  return kSupportsColor;
}

bool IsTerminal(FILE* file) noexcept {
#if defined(OS_WINDOWS)
  return ::_isatty(_fileno(file)) != 0 || IsTerminalImpl(file);
#elif defined(OS_LINUX) || defined(OS_MAC)
  return IsTerminalImpl(file);
#endif
}

bool SupportsAnsi(FILE* file) noexcept {
#if defined(OS_WINDOWS)
  auto handle = GetHANDLE(file);
  if (handle == INVALID_HANDLE_VALUE) {
    return false;
  }

  DWORD dwMode = 0;
  if (!GetConsoleMode(handle, &dwMode)) {
    return false;
  }

  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  if (!SetConsoleMode(handle, dwMode)) {
    return false;
  }
  return true;
#else
  return true;
#endif
}

FILE* GetStandardStream(const std::streambuf* buf) {
  if (buf == std::cout.rdbuf()) {
    return stdout;
  } else if (buf == std::cerr.rdbuf() || buf == std::clog.rdbuf()) {
    return stderr;
  }
  return nullptr;
}

struct StyleToANSI {
  Style style;
  const char* ansi;
};

constexpr std::array<StyleToANSI, 9> kStyleMapping{
    StyleToANSI{Style::kReset, "\033[0m"},
    StyleToANSI{Style::kBold, "\033[1m"},
    StyleToANSI{Style::kFgWhite, "\033[37m"},
    StyleToANSI{Style::kFgRed, "\033[31m"},
    StyleToANSI{Style::kFgGreen, "\033[32m"},
    StyleToANSI{Style::kFgYellow, "\033[33m"},
    StyleToANSI{Style::kFgBlue, "\033[34m"},
    StyleToANSI{Style::kBgRed, "\033[41m"},
    StyleToANSI{Style::kBgGreen, "\033[42m"}};

void UseStyle(std::ostream& output, const Style style) {
  for (const auto& s : kStyleMapping) {
    if (HasStyle(style, s.style)) {
      output << s.ansi;
    }
  }
}

bool CanUseStyle(std::ostream& output) {
  auto* buf = output.rdbuf();
  auto* file = GetStandardStream(buf);

  if (!SupportsColor()) {
    return false;
  }

  if (!IsTerminal(file)) {
    return false;
  }

  if (!SupportsAnsi(file)) {
    return false;
  }

  return true;
}

bool can_use_style = false;
bool first_refresh = false;
}  // namespace
// NOLINTEND
}  // namespace simpletest

namespace std {
std::ostream& refresh(std::ostream& output) {
  ::simpletest::can_use_style = ::simpletest::CanUseStyle(output);
  ::simpletest::first_refresh = true;
  return output;
}
}  // namespace std

std::ostream& operator<<(std::ostream& output, const simpletest::Style style) {
  if (!simpletest::first_refresh) {
    std::refresh(output);
  }

  if (simpletest::can_use_style) {
    simpletest::UseStyle(output, style);
  }

  return output;
}
