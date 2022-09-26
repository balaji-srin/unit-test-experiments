#include "gpio.h"
#include "stddef.h"
#include "variadic_module.h"

int led_init(void)
{
	return gpio_init();
}

int led_fancy_blink(void)
{
	int a;
	char string[] = "FILL";

	variadic_module_get(2, "%d %s", &a, string, NULL);

	return 0;
}
