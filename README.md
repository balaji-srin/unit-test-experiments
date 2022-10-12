# Experiments with unit tests for embedded software

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

## Cmake Configure

    cmake .

## Building

    make

### Running the tests

    ctest
