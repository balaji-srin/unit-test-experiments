#include "gpio.h"

int led_init(void)
{
	return gpio_init();
}

int fun_with_unfreed_memory(void)
{
	char * ptr = (char *)malloc(5);
}

static int fun_alloc(char ** ptr)
{
	*ptr = (char *)malloc(5);
}

static int fun_free(char ** ptr)
{
	free(ptr);
}

int fun_with_calls_funcs_that_do_malloc_and_free(void)
{
	char * ptr;

	fun_alloc(&ptr);

	fun_free(ptr);
}