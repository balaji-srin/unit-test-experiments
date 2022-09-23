#include <stdio.h>
#include <assert.h>

#include "led.h"
#include "unity.h"
#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(int, gpio_init);

void setUp(void)
{
	RESET_FAKE(gpio_init);
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

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_when_led_init_is_called_it_calls_gpio_init_and_returns_success);
	RUN_TEST(test_when_gpio_init_returns_failure_led_init_returns_failure);

	return UNITY_END();
}