#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "led.h"
#include "unity.h"
#include "mock_gpio.h"
#include "mock_variadic_module.h"

/* Stub for variadic_module_get since CMock does not mock variadic functions. */
int variadic_module_get(uint8_t count, const char *fmt, ...)
{
	char test_string[] = "one";
	va_list args;
	va_start(args, fmt);

	TEST_ASSERT_EQUAL_STRING("%d %s", fmt);
	TEST_ASSERT_EQUAL(2, count);

	int *val = va_arg(args, int *);
	char *str = va_arg(args, char *);
	char *last_param = va_arg(args, char *);

	TEST_ASSERT_EQUAL(NULL, last_param);
	*val = 1;

	TEST_ASSERT_GREATER_OR_EQUAL_MESSAGE(strlen(test_string), strlen(str),
					     "String length not sufficient");
	strcpy(str, test_string);

	return 0;
}

void setUp(void)
{
	mock_gpio_Init();
	mock_variadic_module_Init();
}

void tearDown(void)
{
	mock_gpio_Verify();
	mock_variadic_module_Verify();
}

void test_when_led_init_is_called_it_calls_gpio_init_and_returns_success(void)
{
	gpio_init_ExpectAndReturn(0);

	TEST_ASSERT_EQUAL(0, led_init());
}

void test_when_gpio_init_returns_failure_led_init_returns_failure(void)
{
	gpio_init_ExpectAndReturn(-1);

	TEST_ASSERT_EQUAL(-1, led_init());
}

void test_when_led_fancy_blink_is_called_variadic_module_get_is_called(void)
{
	TEST_ASSERT_EQUAL(0, led_fancy_blink());
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_when_led_init_is_called_it_calls_gpio_init_and_returns_success);
	RUN_TEST(test_when_gpio_init_returns_failure_led_init_returns_failure);
	RUN_TEST(test_when_led_fancy_blink_is_called_variadic_module_get_is_called);

	return UNITY_END();
}