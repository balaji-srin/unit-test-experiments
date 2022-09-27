#ifndef __GPIO_H
#define __GPIO_H

/** API to initialize GPIO.
 *
 * @retval 0 on succcess
 * @retval -1 on failure
 */
int gpio_init(void);

/* API that accepts multiple params and returns through reference.
 * @param[out] name Name
 * @param[in] name_len Name length in bytes
 * @param[in] level Level
 * @param[in] drive Drive
 *
 * @retval 0 on succcess
 * @retval -1 on failure
 */
int gpio_config(char *name, uint8_t name_len, int level, int drive);

#endif