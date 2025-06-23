cmake_minimum_required(VERSION 3.20.0)

project(led_driver_test_cmocka)
include(CTest)

set(WORKSPACE_ROOT ${PROJECT_SOURCE_DIR}/../../)
set(CMOCKA_DIR ${WORKSPACE_ROOT}/cmocka/)

# Configure cmocka
execute_process(
	COMMAND
	cmake -B ${CMAKE_BINARY_DIR}/cmocka_build
	WORKING_DIRECTORY ${CMOCKA_DIR}/
)

# Build libcmocka.so
execute_process(
	COMMAND
	make cmocka
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/cmocka_build
)

add_executable(led_driver_test_cmocka led_test.c)

target_include_directories(led_driver_test_cmocka PRIVATE ${CMOCKA_DIR}/include)
target_link_libraries(led_driver_test_cmocka PRIVATE cmocka)
target_link_directories(led_driver_test_cmocka PRIVATE ${CMAKE_BINARY_DIR}/cmocka_build/src/)

target_include_directories(led_driver_test_cmocka PRIVATE ${WORKSPACE_ROOT}/uut/include)
target_include_directories(led_driver_test_cmocka PRIVATE ${WORKSPACE_ROOT}/drivers)

target_sources(led_driver_test_cmocka PRIVATE ${WORKSPACE_ROOT}/uut/src/led.c)
target_sources(led_driver_test_cmocka PRIVATE mocks/mocks.c)

target_link_options(led_driver_test_cmocka PRIVATE "--coverage")

add_test(NAME led_driver_test_cmocka COMMAND ${CMAKE_CURRENT_BINARY_DIR}/led_driver_test_cmocka)

# Include the normalized_get_inline.h so that the inline function get declared as normal function
set_property(SOURCE ${WORKSPACE_ROOT}/uut/src/led.c
	PROPERTY COMPILE_FLAGS "-include ${CMAKE_CURRENT_SOURCE_DIR}/normalized_get_inline.h")

add_custom_target(mutate COMMAND mull-runner-14 led_driver_test_fff)