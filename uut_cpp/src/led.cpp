#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
using namespace std;
#include "gpio_singleton.h"
#include "variadic_module.h"
#include "get_inline.h"
#include "led.h"

// Get the singleton instance of Gpio
Gpio& gpio = Gpio::getInstance();

int Led::init() {
    cout << "Init" << endl;
    return gpio.init();  // Use the singleton Gpio class for initialization
}

int Led::config() {
    const int NAME_LEN = 10;
    char name[NAME_LEN];

    // Use the singleton Gpio class for configuration
    int result = gpio.config(name, sizeof(name), 1, 2);

    // Return 0 if name matches "MagicName", otherwise return -1
    return (std::strcmp(name, "MagicName") == 0) ? 0 : -1;
}
