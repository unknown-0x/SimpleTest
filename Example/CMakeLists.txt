add_executable(
    Example 
    Main.cpp 
    Math.cpp 
    String.cpp
    FloatingPoint.cpp
    Failed.cpp
)

target_include_directories(Example PRIVATE ${ROOT_PATH}/Source/)
target_link_libraries(Example PRIVATE SimpleTest)

target_import_api(Example SimpleTest)
target_enable_clang_format(Example)
# target_enable_clang_tidy(Example)