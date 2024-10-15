#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "gpio_singleton.h"
#include "led.h"

using ::testing::Return;

class MockGpio : public Gpio {
 public:
  MOCK_METHOD(int, init, (), (override));
  MOCK_METHOD(int, config, (char* name, uint8_t name_len, int level, int drive), (override));
};

// Declare external mock function
extern Gpio& getInstance();

// Create a fake version of getInstance() that returns the mock singleton
Gpio& getInstance() {
  static MockGpio mockInstance;
  return mockInstance;
}

TEST(test_when_led_init_is_called_it_calls_gpio_init_and_returns_success, GpioInit) {
  // Cast the singleton instance from Gpio& to MockGpio& to access mock-specific methods
  MockGpio& mockgpio = dynamic_cast<MockGpio&>(getInstance());

  EXPECT_CALL(mockgpio, init()).Times(1);

  Led led;

  EXPECT_EQ(0, led.init());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(throw_on_failure) = true; // Fail on unmet expectations
    return RUN_ALL_TESTS();
}