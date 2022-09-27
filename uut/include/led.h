#ifndef __LED_H
#define __LED_H

int led_init(void);

/* Function that calls a variadic function. */
int led_fancy_blink(void);

/* Function that calls an inline function. */
void led_light_up(void);

/* Function that calls another function that takes in multiple arguments and returns array by
 * reference.
 */
int led_config();

#endif