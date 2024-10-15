#ifndef LED_H
#define LED_H

#include <cstddef>
#include <cstdint>

class Led {
public:
    // Public methods for LED functionality
    int init();
    void light_up();
    int config();
};

#endif // LED_H
