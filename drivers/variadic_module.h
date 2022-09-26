#ifndef __VARIADIC_MODULE_H
#include <stdint.h>

/** An fancy variadic API
 *
 * @param[in] count Number of parameters to be fetched
 * @param[in] fmt Format specifier for the parameters to be fetched.
 *
 * After the format specifier, a list of pointers to store the data fetched. Since there is
 * no way to validate the number of parameters passed, after providing the required number of
 * parameters, a NULL pointer is expected for sanity checking. For example, if you want to fetch
 * one integer and a character string, you should invoke this function as follows
 * variadic_module_get(2, "%d %s", &integer, @char_array, NULL);
 * where char_array shall be a null terminated string.
 *
 * @retval 0 on success
 * @retval -1 on failure
 */
int variadic_module_get(uint8_t count, const char *fmt, ...);

#endif