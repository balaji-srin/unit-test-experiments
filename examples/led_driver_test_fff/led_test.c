#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include "led.h"
#include "unity.h"
#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(int, gpio_init);
FAKE_VALUE_FUNC_VARARG(int, variadic_module_get, uint8_t, const char *, ...);
FAKE_VOID_FUNC(variadic_module_init);
FAKE_VALUE_FUNC(int, get_inline, int);
FAKE_VALUE_FUNC(int, gpio_config, char *, uint8_t, int, int);

static int variadic_module_get_that_gets_1_and_one(uint8_t count, const char *fmt, va_list args)
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
	RESET_FAKE(variadic_module_init);
}

void tearDown(void)
{
	/* Do nothing. */
}

static void test_when_led_init_is_called_it_calls_gpio_init_and_returns_success(void)
{
	gpio_init_fake.return_val = 0;

	TEST_ASSERT_EQUAL(0, led_init());

	TEST_ASSERT_EQUAL(1, gpio_init_fake.call_count);
}

static void test_when_gpio_init_returns_failure_led_init_returns_failure(void)
{
	gpio_init_fake.return_val = -1;

	TEST_ASSERT_EQUAL(-1, led_init());
}

/* Two tests to demonstrate that we can split a big test to two small tests if need be. */
static void test_when_led_fancy_blink_is_called_variadic_module_get_is_called(void)
{
	variadic_module_get_fake.custom_fake = variadic_module_get_that_gets_1_and_one;

	TEST_ASSERT_EQUAL(0, led_fancy_blink());
	TEST_ASSERT_EQUAL(1, variadic_module_get_fake.call_count);
}

static void test_when_led_fancy_blink_is_called_variadic_module_init_is_called(void)
{
	TEST_ASSERT_EQUAL(0, led_fancy_blink());
	TEST_ASSERT_EQUAL(1, variadic_module_init_fake.call_count);
}

/* Test that demonstrates mocking inline functions. */
static void test_when_led_light_up_is_called_the_get_inline_set_is_called(void)
{
	led_light_up();
	TEST_ASSERT_EQUAL(1, get_inline_fake.call_count);
	TEST_ASSERT_EQUAL(1, get_inline_fake.arg0_val);
}

#define MIN(a, b) (a < b ? a : b)
/* Need custom fakes because thats the only way to return a array by pointer. */
static int gpio_config_that_returns_MagicName(char *name, uint8_t name_len, int level, int drive)
{
	static char name_to_return[] = "MagicName";

	/* These two parameters need not be cared for here. */
	(void) level;
	(void) drive;

	strncpy(name, name_to_return, MIN(name_len, sizeof(name_to_return)));

	return 0;
}

static int gpio_config_that_does_not_return_MagicName(char *name, uint8_t name_len, int level,
						      int drive)
{
	static char name_to_return[] = "NotMagic";

	/* These two parameters need not be cared for here. */
	(void) level;
	(void) drive;
	strncpy(name, name_to_return, MIN(name_len, sizeof(name_to_return)));

	return 0;
}

/* Tests that demonstrate how to validate multiple parms and return array by pointer. */
static void test_when_gpio_config_returns_MagicName_led_config_returns_0(void)
{
	const uint8_t exp_name_len = 10;
	const uint8_t exp_level = 1;
	const uint8_t exp_drive = 2;

	gpio_config_fake.custom_fake = gpio_config_that_returns_MagicName;

	TEST_ASSERT_EQUAL(0, led_config());

	TEST_ASSERT_EQUAL(exp_name_len, gpio_config_fake.arg1_val);
	TEST_ASSERT_EQUAL(exp_level, gpio_config_fake.arg2_val);
	TEST_ASSERT_EQUAL(exp_drive, gpio_config_fake.arg3_val);
}

static void test_when_gpio_config_does_not_return_MagicName_led_config_returns_minus_one(void)
{
	const uint8_t exp_name_len = 10;
	const uint8_t exp_level = 1;
	const uint8_t exp_drive = 2;

	gpio_config_fake.custom_fake = gpio_config_that_does_not_return_MagicName;

	TEST_ASSERT_EQUAL(-1, led_config());

	TEST_ASSERT_EQUAL(exp_name_len, gpio_config_fake.arg1_val);
	TEST_ASSERT_EQUAL(exp_level, gpio_config_fake.arg2_val);
	TEST_ASSERT_EQUAL(exp_drive, gpio_config_fake.arg3_val);
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_when_led_init_is_called_it_calls_gpio_init_and_returns_success);
	RUN_TEST(test_when_gpio_init_returns_failure_led_init_returns_failure);
	RUN_TEST(test_when_led_fancy_blink_is_called_variadic_module_get_is_called);
	RUN_TEST(test_when_led_fancy_blink_is_called_variadic_module_init_is_called);
	RUN_TEST(test_when_led_light_up_is_called_the_get_inline_set_is_called);
	RUN_TEST(test_when_gpio_config_returns_MagicName_led_config_returns_0);
	RUN_TEST(test_when_gpio_config_does_not_return_MagicName_led_config_returns_minus_one);

	return UNITY_END();
}