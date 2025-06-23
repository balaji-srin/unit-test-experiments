cmake_minimum_required(VERSION 3.20.0)

project(UnitTestExperiments)

include(CTest)

set(CMOCKA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmocka)

add_compile_options(-Werror -Wall -g -O0 --coverage)

# Define default for MUTATION_TESTING if not set
option(MUTATION_TESTING "Enable mutation testing" OFF)

set(MUTATION_EXECUTABLES)

if(MUTATION_TESTING)
    message(STATUS "Enabling mutation testing")
    message(STATUS "Mutation testing is only tested to work with the clang-14 compiler.")

    # Mull (the mutation testing tool) specific
    add_compile_options(-fpass-plugin=/usr/lib/mull-ir-frontend-14 -fexperimental-new-pass-manager -grecord-command-line)

    add_custom_target(mutate COMMAND ${CMAKE_COMMAND})
endif()

add_subdirectory(examples)
