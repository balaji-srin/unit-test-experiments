#include "gpio.h"

int led_init(void)
{
	return gpio_init();
}

int buggy_led_init(void)
{
	int err = gpio_init();

	switch (err) {
	case 0:
		return 1;
	case 1:
		return 0;
	case 3:
		return 0;
	}
	return -1;
}
