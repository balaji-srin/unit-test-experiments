cmake_minimum_required(VERSION 3.20.0)
project(led_driver_test_cmock)

include(CTest)
set(WORKSPACE_ROOT ${PROJECT_SOURCE_DIR}/../../)

set(CMOCK_DIR ${WORKSPACE_ROOT}/CMock)

function(cmock_manage target header_file_path)
	# Get the file name without extension and the path
	get_filename_component(file_to_mock ${header_file_path} NAME_WE)
	# Create a rule to make the mocked implementation
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mocks/mock_${file_to_mock}.c
		COMMAND
		ruby
		${CMOCK_DIR}/lib/cmock.rb
		-o${CMAKE_CURRENT_LIST_DIR}/cmock_cfg.yaml
		${header_file_path}
		--mock_prefix=mock_
		--mock_path=${CMAKE_CURRENT_BINARY_DIR}/mocks
		DEPENDS ${CMAKE_CURRENT_LIST_DIR}/cmock_cfg.yaml ${header_file_path}
	)
	# Include the above generated file to the target
	target_sources(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/mocks/mock_${file_to_mock}.c)

	# Add the include directory containing the mock header file
	target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/mocks)

	# Include CMock implementation to target and its include path
	target_sources(${target} PRIVATE ${CMOCK_DIR}/src/cmock.c)
	target_include_directories(${target} PRIVATE ${CMOCK_DIR}/src)
endfunction()


add_executable(led_driver_test_cmock led_test.c)

cmock_manage(${PROJECT_NAME} ${WORKSPACE_ROOT}/drivers/gpio.h)
cmock_manage(${PROJECT_NAME} ${WORKSPACE_ROOT}/drivers/get_inline.h)
cmock_manage(${PROJECT_NAME} ${WORKSPACE_ROOT}/drivers/variadic_module.h)

target_include_directories(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/uut/include)
target_include_directories(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/Unity/src)
target_include_directories(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/drivers)

target_sources(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/uut/src/led.c)
target_sources(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/Unity/src/unity.c)

target_link_options(led_driver_test_cmock PRIVATE "--coverage")

add_test(NAME led_driver_test_cmock COMMAND ${CMAKE_CURRENT_BINARY_DIR}/led_driver_test_cmock)
