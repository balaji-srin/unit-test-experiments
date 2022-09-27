cmake_minimum_required(VERSION 3.20.0)
project(led_driver_test_cmock)

include(CTest)

set(WORKSPACE_ROOT ${PROJECT_SOURCE_DIR}/../../)

add_executable(led_driver_test_cmock led_test.c)

cmock_manage(${PROJECT_NAME} ${WORKSPACE_ROOT}/drivers/gpio.h)
cmock_manage(${PROJECT_NAME} ${WORKSPACE_ROOT}/drivers/get_inline.h)
cmock_manage(${PROJECT_NAME} ${WORKSPACE_ROOT}/drivers/variadic_module.h)

target_include_directories(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/uut/include)
target_include_directories(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/Unity/src)
target_include_directories(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/drivers)

target_sources(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/uut/src/led.c)
target_sources(led_driver_test_cmock PRIVATE ${WORKSPACE_ROOT}/Unity/src/unity.c)

target_compile_options(led_driver_test_cmock PRIVATE "--coverage")
target_link_options(led_driver_test_cmock PRIVATE "--coverage")

add_test(NAME led_driver_test_cmock COMMAND ${CMAKE_CURRENT_BINARY_DIR}/led_driver_test_cmock)
