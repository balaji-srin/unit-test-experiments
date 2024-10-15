#ifndef GPIO_H
#define GPIO_H

#include <cstddef>
#include <cstdint>
#include <iostream>
using namespace std;

class Gpio {
public:
    // Get the singleton instance of Gpio
    static Gpio& getInstance() {
        static Gpio instance;
        return instance;
    }

    /** API to initialize GPIO.
     *
     * @retval 0 on success
     * @retval -1 on failure
     */
    virtual int init()
    {
        cout << "Virtual Init" << endl;
         return 0;
    }

    /* API that accepts multiple parameters and returns through reference.
     * @param[out] name Name
     * @param[in] name_len Name length in bytes
     * @param[in] level Level
     * @param[in] drive Drive
     *
     * @retval 0 on success
     * @retval -1 on failure
     */
    virtual int config(char* name, uint8_t name_len, int level, int drive)
    {
        return 0;
    }


    // Deleted copy constructor and assignment operator
    Gpio(const Gpio&) = delete;
    void operator=(const Gpio&) = delete;

protected:
    Gpio() {}

private:
    // Internal private methods for the actual implementation
    int gpio_init_impl();
    int gpio_config_impl(char* name, uint8_t name_len, int level, int drive);
};

#endif // GPIO_H
