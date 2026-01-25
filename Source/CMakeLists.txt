add_library(
    SimpleTest 

    SimpleTest/Style.hpp
    SimpleTest/Style.cpp
    SimpleTest/TextBuffer.hpp
    SimpleTest/TextBuffer.cpp
    SimpleTest/Reporter.hpp
    SimpleTest/ConsoleReporter.hpp
    SimpleTest/ConsoleReporter.cpp
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
    SimpleTest/TestSummary.hpp
    SimpleTest/UnitTest.cpp
    SimpleTest/UnitTest.hpp
)

target_export_api(SimpleTest SIMPLETEST_API)
target_enable_clang_format(SimpleTest)
target_config_build_type(SimpleTest)
# target_enable_clang_tidy(SimpleTest)