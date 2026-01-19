add_library(
    External
    Utils/Utils.hpp
    Utils/Utils.cpp
)

target_export_api(External UTILS_API)
target_config_build_type(External)
target_enable_clang_format(External)
target_enable_clang_tidy(External)
