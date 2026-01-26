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

add_library(SimpleTest::SimpleTest ALIAS SimpleTest)

target_include_directories(SimpleTest
  PUBLIC
    $<BUILD_INTERFACE:${ROOT_PATH}/Source>
    $<INSTALL_INTERFACE:include>
)

target_export_api(SimpleTest SIMPLETEST_API)
target_enable_clang_format(SimpleTest)
target_config_build_type(SimpleTest)
# target_enable_clang_tidy(SimpleTest)