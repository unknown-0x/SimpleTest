add_library(
    SimpleTest 
    SimpleTest/SimpleTest.cpp
    SimpleTest/SimpleTest.hpp
    SimpleTest/TestCase.cpp
    SimpleTest/TestCase.hpp
    SimpleTest/TestSuite.cpp
    SimpleTest/TestSuite.hpp
    SimpleTest/TestMacros.cpp
    SimpleTest/TestMacros.hpp
    SimpleTest/TestRunner.cpp
    SimpleTest/TestRunner.hpp
)

target_export_api(SimpleTest SIMPLETEST_API)
target_enable_clang_format(SimpleTest)
# target_enable_clang_tidy(SimpleTest)