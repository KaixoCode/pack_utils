cmake_minimum_required (VERSION 3.0)
project (pack_utils)

set (CMAKE_CXX_STANDARD 23)

add_executable(pack_utils_example
  "${pack_utils_SOURCE_DIR}/pack_utils.hpp"
  "${pack_utils_SOURCE_DIR}/example.cpp"
)

target_include_directories(pack_utils_example PUBLIC
  "${pack_utils_SOURCE_DIR}"
)