#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>
#include <string.h>

extern char *mock_gpio_config_name_to_return;

int gpio_init(void)
{
	return mock_type(int);
}

int gpio_config(char *name, uint8_t name_len, int level, int drive)
{
	assert_non_null(name);
	check_expected(name_len);
	check_expected(level);
	check_expected(drive);

	assert_non_null(mock_gpio_config_name_to_return);

	assert_true(strlen(mock_gpio_config_name_to_return) <= name_len);

	strncpy(name, mock_gpio_config_name_to_return, strlen(mock_gpio_config_name_to_return));

	return mock_type(int);
}

int variadic_module_get(uint8_t count, const char *fmt, ...)
{
	check_expected(count);
	check_expected(fmt);

	char test_string[] = "one";
	va_list args;
	va_start(args, fmt);

	int *val = va_arg(args, int *);
	char *str = va_arg(args, char *);
	char *last_param = va_arg(args, char *);

	assert_null(last_param);
	*val = 1;
	assert_true(strlen(test_string) <= strlen(str));
	strcpy(str, test_string);

	return mock_type(int);
}

void variadic_module_init(void)
{
	function_called();
}

int get_inline(int val)
{
	check_expected(val);

	return mock_type(int);
}
