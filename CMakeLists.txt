cmake_minimum_required(VERSION 3.20.0)

project(UnitTestExperiments)

include(CTest)

set(CMOCKA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmocka)

add_compile_options(-Werror -Wall -g -O0 --coverage)

# Mull (the mutation testing tool) specific
add_compile_options(-fpass-plugin=/usr/lib/mull-ir-frontend-14 -fexperimental-new-pass-manager -grecord-command-line)

add_subdirectory(examples)
