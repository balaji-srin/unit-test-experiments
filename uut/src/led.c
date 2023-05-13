#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "gpio.h"
#include "variadic_module.h"
#include "get_inline.h"

int led_init(void)
{
	if (gpio_init() == 0)
	{
		return 0;
	}
	else
	{
		return gpio_init();
	}
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

int led_config()
{
#define NAME_LEN 10
	char name[NAME_LEN];

	gpio_config(name, sizeof(name), 1, 2);

	return (strcmp(name, "MagicName") == 0) ? 0 : -1;
}
