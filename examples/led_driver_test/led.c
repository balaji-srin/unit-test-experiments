#include "gpio.h"
#include <stdbool.h>

int led_init(void)
{
	return gpio_init();
}

static bool init_my_value;

static int func_to_initialize_stuff(int *ptr)
{
	if (init_my_value == false) {
		return -1;
	}
	*ptr = 1;

	return 0;
}

/* Sonar should not complain */
int func_that_accesses_stuff_inited_by_another_func(void)
{
	init_my_value = true;
	int i;
	int err = func_to_initialize_stuff(&i);

	if (err != 0) {
		return err;
	}

	if (i == 1) {
		led_init();
	}

	return 0;
}

/* Sonar should complain */
int func_that_accesses_stuff_not_inited_by_another_func(void)
{
	init_my_value = false;
	int i;
	int err = func_to_initialize_stuff(&i);

	if (i == 1) {
		led_init();
	}

	return 0;
}
