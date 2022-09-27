#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "led.h"
#include "unity.h"
#include "mock_gpio.h"
#include "mock_variadic_module.h"
#include "mock_get_inline.h"

static uint8_t variadic_module_get_called_count;

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

	variadic_module_get_called_count++;

	return 0;
}

void setUp(void)
{
	mock_gpio_Init();
	mock_variadic_module_Init();
	mock_get_inline_Init();
}

void tearDown(void)
{
	mock_gpio_Verify();
	mock_variadic_module_Verify();
	mock_get_inline_Verify();
}

static void test_when_led_init_is_called_it_calls_gpio_init_and_returns_success(void)
{
	gpio_init_ExpectAndReturn(0);

	TEST_ASSERT_EQUAL(0, led_init());
}

static void test_when_gpio_init_returns_failure_led_init_returns_failure(void)
{
	gpio_init_ExpectAndReturn(-1);

	TEST_ASSERT_EQUAL(-1, led_init());
}

static void test_when_led_fancy_blink_is_called_variadic_module_get_is_called(void)
{
	variadic_module_init_Expect();
	TEST_ASSERT_EQUAL(0, led_fancy_blink());

	/* Also assert that the custom variadic stub was called once. */
	TEST_ASSERT_EQUAL(1, variadic_module_get_called_count);
}

/* Test that demonstrates mocking inline functions. */
static void test_when_led_light_up_is_called_the_get_inline_is_called(void)
{
	get_inline_ExpectAndReturn(1, 0);
	led_light_up();
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_when_led_init_is_called_it_calls_gpio_init_and_returns_success);
	RUN_TEST(test_when_gpio_init_returns_failure_led_init_returns_failure);
	RUN_TEST(test_when_led_fancy_blink_is_called_variadic_module_get_is_called);
	RUN_TEST(test_when_led_light_up_is_called_the_get_inline_is_called);

	return UNITY_END();
}