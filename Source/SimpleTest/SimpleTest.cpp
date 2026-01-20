#include "SimpleTest.hpp"

namespace simpletest {
namespace {
#if defined(_MSC_VER) && defined(DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
void EnableMemoryLeakDetection() {
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
#else
void EnableMemoryLeakDetection() {}
#endif
}  // namespace

int Main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  EnableMemoryLeakDetection();
  return TestRunner::Get().RunAllTests();
}
}  // namespace simpletest
