cmake_minimum_required(VERSION 3.20.0)

project(UnitTestExperiments)

include(CTest)

set(CMOCK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CMock)
set(CMOCKA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmocka)

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

add_compile_options(-Werror -Wall -g -O0 --coverage)

add_subdirectory(examples)

