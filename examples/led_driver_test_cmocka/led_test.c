#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>

#include "led.h"

char *mock_gpio_config_name_to_return;

static void test_when_led_init_is_called_it_calls_gpio_init_and_returns_success(void **state)
{
	(void)state; /* unused */
	will_return(gpio_init, 0);

	assert_int_equal(0, led_init());
}

static void test_when_gpio_init_returns_failure_led_init_returns_failure(void **state)
{
	(void)state; /* unused */
	will_return(gpio_init, -1);

	assert_int_equal(-1, led_init());
}

static void test_when_led_fancy_blink_is_called_variadic_module_get_is_called(void **state)
{
	(void)state; /* unused */

	expect_function_call(variadic_module_init);

	will_return(variadic_module_get, 0);
	expect_value(variadic_module_get, count, 2);
	expect_string(variadic_module_get, fmt, "%d %s");

	assert_int_equal(0, led_fancy_blink());
}

/* Test to demonstrate the workaround to mock inline function.*/
static void test_when_led_light_up_is_called_the_get_inline_is_called(void **state)
{
	(void)state; /* unused */

	will_return(get_inline, 0);
	expect_value(get_inline, val, 1);

	led_light_up();
}

/* Tests that demonstrate how to validate multiple parms and return array by pointer. */
static void test_when_gpio_config_returns_MagicName_led_config_returns_0(void **state)
{
	(void)state; /* unused */

	const uint8_t exp_name_len = 10;
	const uint8_t exp_level = 1;
	const uint8_t exp_drive = 2;
	char name_to_return[] = "MagicName";

	expect_value(gpio_config, name_len, exp_name_len);
	expect_value(gpio_config, level, exp_level);
	expect_value(gpio_config, drive, exp_drive);

	will_return(gpio_config, NULL);
	mock_gpio_config_name_to_return = name_to_return;

	assert_int_equal(0, led_config());
}

static void
test_when_gpio_config_does_not_return_MagicName_led_config_returns_minus_one(void **state)
{
	(void)state; /* unused */

	const uint8_t exp_name_len = 10;
	const uint8_t exp_level = 1;
	const uint8_t exp_drive = 2;
	char name_to_return[] = "NotMagic";

	expect_value(gpio_config, name_len, exp_name_len);
	expect_value(gpio_config, level, exp_level);
	expect_value(gpio_config, drive, exp_drive);

	will_return(gpio_config, NULL);
	mock_gpio_config_name_to_return = name_to_return;

	assert_int_equal(-1, led_config());
}

const struct CMUnitTest test_suite[] = {
	cmocka_unit_test(test_when_led_init_is_called_it_calls_gpio_init_and_returns_success),
	cmocka_unit_test(test_when_gpio_init_returns_failure_led_init_returns_failure),
	cmocka_unit_test(test_when_led_fancy_blink_is_called_variadic_module_get_is_called),
	cmocka_unit_test(test_when_led_light_up_is_called_the_get_inline_is_called),
	cmocka_unit_test(test_when_gpio_config_returns_MagicName_led_config_returns_0),
	cmocka_unit_test(
		test_when_gpio_config_does_not_return_MagicName_led_config_returns_minus_one),
};

int main(void)
{
	return cmocka_run_group_tests(test_suite, NULL, NULL);
}
