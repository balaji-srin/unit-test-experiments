#include <stdio.h>
#include <assert.h>

#include "led.h"
#include "unity.h"
#include "mock_gpio.h"

void setUp(void)
{
	mock_gpio_Init();
}

void tearDown(void)
{
	mock_gpio_Verify();
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

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_when_led_init_is_called_it_calls_gpio_init_and_returns_success);
	RUN_TEST(test_when_gpio_init_returns_failure_led_init_returns_failure);

	return UNITY_END();
}