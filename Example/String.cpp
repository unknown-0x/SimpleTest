#include <SimpleTest/SimpleTest.hpp>

#include <string>

TEST_CASE(String, StdString) {
  const std::string a{"string"};
  const std::string b{"string"};
  const std::string c{"aaaaaa"};

  CHECK_EQ(a, b);
  CHECK_NE(a, c);

  CHECK_STREQ(a, b);
  CHECK_STRNE(a, c);
}

TEST_CASE(String, StdWString) {
  const std::wstring a{L"string"};
  const std::wstring b{L"string"};
  const std::wstring c{L"aaaaaa"};

  CHECK_EQ(a, b);
  CHECK_NE(a, c);

  CHECK_STREQ(a, b);
  CHECK_STRNE(a, c);
}

TEST_CASE(String, StdU32String) {
  const std::u32string a{U"string"};
  const std::u32string b{U"string"};
  const std::u32string c{U"aaaaaa"};

  CHECK_EQ(a, b);
  CHECK_NE(a, c);

  CHECK_STREQ(a, b);
  CHECK_STRNE(a, c);
}

TEST_CASE(String, ConstCharP) {
  CHECK_STREQ("hello", "hello");
  CHECK_STRNE("hello", "world");
}

TEST_CASE(String, ConstWCharP) {
  CHECK_STREQ(L"hello", L"hello");
  CHECK_STRNE(L"hello", L"world");
}

TEST_CASE(String, ConstChar32P) {
  CHECK_STREQ(U"hello", U"hello");
  CHECK_STRNE(U"hello", U"world");
}