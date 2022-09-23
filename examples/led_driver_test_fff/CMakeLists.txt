cmake_minimum_required(VERSION 3.20.0)
project(led_driver_test_fff)

include(CTest)

add_executable(led_driver_test_fff led_test.c)

set(WORKSPACE_ROOT ${PROJECT_SOURCE_DIR}/../../)

target_include_directories(led_driver_test_fff PRIVATE ${WORKSPACE_ROOT}/uut/include)
target_include_directories(led_driver_test_fff PRIVATE ${WORKSPACE_ROOT}/fff)
target_include_directories(led_driver_test_fff PRIVATE ${WORKSPACE_ROOT}/Unity/src)
target_include_directories(led_driver_test_fff PRIVATE ${WORKSPACE_ROOT}/drivers)

target_sources(led_driver_test_fff PRIVATE ${WORKSPACE_ROOT}/uut/src/led.c)
target_sources(led_driver_test_fff PRIVATE ${WORKSPACE_ROOT}/Unity/src/unity.c)

# Add a target so that 'ninja unittest' builds and runs the unit test.
add_custom_target(
	unittest
	DEPENDS led_driver_test_fff
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/led_driver_test_fff
)

target_compile_options(led_driver_test_fff PRIVATE "--coverage")
target_link_options(led_driver_test_fff PRIVATE "--coverage")

add_test(NAME led_driver_test_fff COMMAND ${CMAKE_CURRENT_BINARY_DIR}/led_driver_test_fff)
