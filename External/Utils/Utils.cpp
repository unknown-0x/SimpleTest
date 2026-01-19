#include "Utils.hpp"

#include <iostream>

namespace utils {
void Hello() {
#if DEBUG
  std::cout << "[DEBUG] Hello world\n";
#elif RELEASE
  std::cout << "[RELEASE] Hello world\n";
#endif
}
}  // namespace utils