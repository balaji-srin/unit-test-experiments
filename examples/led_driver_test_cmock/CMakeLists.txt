cmake_minimum_required(VERSION 3.20.0)
project(led_driver_test_cmock)

include(CTest)

set(WORKSPACE_ROOT ${PROJECT_SOURCE_DIR}/../../)

add_executable(led_driver_test_cmock led_test.c)


add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mocks/mock_gpio.c
	COMMAND
	ruby
	${WORKSPACE_ROOT}/CMock/lib/cmock.rb
	${WORKSPACE_ROOT}/drivers/gpio.h
	--mock_prefix=mock_
	--mock_path=${CMAKE_CURRENT_BINARY_DIR}/mocks
)

target_include_directories(led_driver_test_cmock PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/mocks)
target_include_directories(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/CMock/src)
target_sources(led_driver_test_cmock PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/mocks/mock_gpio.c)
target_sources(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/CMock/src/cmock.c)

target_include_directories(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/uut/include)
target_include_directories(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/Unity/src)
target_include_directories(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/drivers)

target_sources(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/uut/src/led.c)
target_sources(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/Unity/src/unity.c)

target_compile_options(led_driver_test_cmock PRIVATE "--coverage")
target_link_options(led_driver_test_cmock PRIVATE "--coverage")

add_test(NAME led_driver_test_cmock COMMAND ${CMAKE_CURRENT_BINARY_DIR}/led_driver_test_cmock)
