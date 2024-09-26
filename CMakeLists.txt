cmake_minimum_required(VERSION 3.20.0)

project(UnitTestExperiments)

include(CTest)

set(CMOCKA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmocka)

add_compile_options(-Werror -Wall -g -O0 --coverage -fprofile-arcs -ftest-coverage)

add_subdirectory(examples)

