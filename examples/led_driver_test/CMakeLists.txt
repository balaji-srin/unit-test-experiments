cmake_minimum_required(VERSION 3.20.0)

project(led_driver_test)

# Glob the sources and add them to the app
FILE(GLOB app_sources *.c)

add_executable(led_driver_test ${app_sources})

set(WORKSPACE_ROOT ${PROJECT_SOURCE_DIR}/../../)

target_include_directories(led_driver_test PRIVATE ${WORKSPACE_ROOT}/fff)
target_include_directories(led_driver_test PRIVATE ${WORKSPACE_ROOT}/Unity/src)
target_include_directories(led_driver_test PRIVATE ${WORKSPACE_ROOT}/drivers)

target_sources(led_driver_test PRIVATE ${app_sources})
target_sources(led_driver_test PRIVATE ${WORKSPACE_ROOT}/Unity/src/unity.c)

add_custom_target(
	test
	DEPENDS led_driver_test
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/led_driver_test
)