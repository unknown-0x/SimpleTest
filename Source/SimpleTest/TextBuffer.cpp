#include "TextBuffer.hpp"

namespace simpletest {
TextBuffer::TextBuffer(std::size_t initial_capacity) {
  buffer_.reserve(initial_capacity);
}

void TextBuffer::Clear() {
  buffer_.clear();
}

TextBuffer& TextBuffer::operator<<(const char* s) {
  return Append(s, std::strlen(s));
}

TextBuffer& TextBuffer::operator<<(char c) {
  return Append(&c, 1);
}

TextBuffer& TextBuffer::operator<<(const std::string& s) {
  return Append(s.data(), s.size());
}

TextBuffer& TextBuffer::operator<<(std::string_view sv) {
  return Append(sv.data(), sv.size());
}

TextBuffer& TextBuffer::operator<<(const TextBuffer& value) {
  return Append(value.buffer_.data(), value.buffer_.size());
}

TextBuffer::Precision TextBuffer::SetPrecision(int precision) {
  precision_.value = precision;
  return precision_;
}

TextBuffer& TextBuffer::operator<<(const Precision /*precision*/) {
  return *this;
}

TextBuffer& TextBuffer::Append(const char* s, size_t count) {
  buffer_.append(s, count);
  return *this;
}
}  // namespace simpletest