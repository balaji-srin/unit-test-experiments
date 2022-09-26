#include <stdio.h>
#include <assert.h>

#include "led.h"
#include "unity.h"
#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(int, gpio_init);
FAKE_VALUE_FUNC_VARARG(int, variadic_module_get, uint8_t, const char *, ...);

static int variadic_module_get_that_gets_1_and_one(uint8_t count, const char *fmt, const va_list args)
{
	char test_string[] = "one";

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
	RESET_FAKE(gpio_init);
	RESET_FAKE(variadic_module_get);
}

void tearDown(void)
{
	/* Do nothing. */
}

void test_when_led_init_is_called_it_calls_gpio_init_and_returns_success(void)
{
	gpio_init_fake.return_val = 0;

	TEST_ASSERT_EQUAL(0, led_init());

	TEST_ASSERT_EQUAL(1, gpio_init_fake.call_count);
}

void test_when_gpio_init_returns_failure_led_init_returns_failure(void)
{
	gpio_init_fake.return_val = -1;

	TEST_ASSERT_EQUAL(-1, led_init());
}

void test_when_led_fancy_blink_is_called_variadic_module_get_is_called(void)
{
	variadic_module_get_fake.custom_fake = variadic_module_get_that_gets_1_and_one;

	TEST_ASSERT_EQUAL(0, led_fancy_blink());
	TEST_ASSERT_EQUAL(1, variadic_module_get_fake.call_count);
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_when_led_init_is_called_it_calls_gpio_init_and_returns_success);
	RUN_TEST(test_when_gpio_init_returns_failure_led_init_returns_failure);
	RUN_TEST(test_when_led_fancy_blink_is_called_variadic_module_get_is_called);

	return UNITY_END();
}