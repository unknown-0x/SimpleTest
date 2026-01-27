add_executable(
    Example 
    Math.cpp 
    String.cpp
    FloatingPoint.cpp
    Failed.cpp
    Fixture.cpp
)

target_link_libraries(Example PRIVATE SimpleTestMain)

target_enable_clang_format(Example)
# target_enable_clang_tidy(Example)