#include <stddef.h>
#include "gpio.h"
#include "variadic_module.h"
#include "get_inline.h"

int led_init(void)
{
	return gpio_init();
}

int led_fancy_blink(void)
{
	int a;
	char string[] = "FILL";

	variadic_module_init();
	variadic_module_get(2, "%d %s", &a, string, NULL);

	return 0;
}

void led_light_up(void)
{
	get_inline(1);
}
