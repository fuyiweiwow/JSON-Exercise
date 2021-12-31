cmake_minimum_required (VERSION 3.0)
project (LFJSON C)

add_library(lfjson lfjson.c)
add_executable(lfjson_test lftest.c)
target_link_libraries(lfjson_test lfjson)
