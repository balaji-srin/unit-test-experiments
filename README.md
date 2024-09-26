cd# Experiments with unit tests for embedded software

This repo contains simple unit tests to demonstrate how to use the following frameworks for unit-testing embedded applications.

- [CMock](https://github.com/ThrowTheSwitch/CMock)
- [Fake Function Framework](https://github.com/meekrosoft/fff)
- [cmocka](https://cmocka.org/)
- [Unity](https://github.com/ThrowTheSwitch/Unity)

Also contained here are some basic github workflows.

[![Compile and unit test](https://github.com/balaji-nordic/unit-test-experiments/actions/workflows/compile_and_test.yml/badge.svg)](https://github.com/balaji-nordic/unit-test-experiments/actions/workflows/compile_and_test.yml)
[![CodeSonar](https://github.com/balaji-nordic/unit-test-experiments/actions/workflows/sonarcloud.yml/badge.svg)](https://github.com/balaji-nordic/unit-test-experiments/actions/workflows/sonarcloud.yml)
[![clang-format Check](https://github.com/balaji-nordic/unit-test-experiments/actions/workflows/clangformat.yml/badge.svg)](https://github.com/balaji-nordic/unit-test-experiments/actions/workflows/clangformat.yml)

Here's how you build and run the unit tests.

## Initialize git submodules (first time only)

    git submodule init
    git submodule update

## Cmake Configure

    cmake .

## Building

    make

### Running the tests

    ctest

### Architecture diagram

Below is the architecture diagram showing the unit under test and its dependent modules.
In this repo, there are tests suites that mock the dependencies and test the APIs exposed by led.h.
The tests can be found under `examples` folder. The names of the folders indicate the mocking framework that is used.

                                   +----------+
                                   |   led.c  |   -> Unit under test
                                   +----------+
                                  /     |     \
                                 /      |      \
                                /       |       \
                               /        |        \
              +-----------------+  +----------+  +------------+
              | variadic_module |  |   gpio   |  | get_inline |-> Dependencies that will be mocked
              +-----------------+  +----------+  +------------+

