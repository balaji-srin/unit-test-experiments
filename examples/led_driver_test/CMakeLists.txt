cmake_minimum_required(VERSION 3.20.0)
project(led_driver_test)

include(CTest)

# Glob the sources and add them to the app
FILE(GLOB app_sources *.c)

add_executable(led_driver_test ${app_sources})

set(WORKSPACE_ROOT ${PROJECT_SOURCE_DIR}/../../)

target_include_directories(led_driver_test PRIVATE ${WORKSPACE_ROOT}/fff)
target_include_directories(led_driver_test PRIVATE ${WORKSPACE_ROOT}/Unity/src)
target_include_directories(led_driver_test PRIVATE ${WORKSPACE_ROOT}/drivers)

target_sources(led_driver_test PRIVATE ${app_sources})
target_sources(led_driver_test PRIVATE ${WORKSPACE_ROOT}/Unity/src/unity.c)

# Add a target so that 'ninja unittest' builds and runs the unit test.
add_custom_target(
	unittest
	DEPENDS led_driver_test
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/led_driver_test
)
add_test(NAME led_driver_test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/led_driver_test)
