#include <mbed.h>
#include "config.h"

#ifdef IS_PLATFORM_IO
#include "PlatformIO_test/GPIO.h"
#else
#include "MBED_test/GPIO.h"
#endif

int main() {

  #if (TEST_PERIPHERALS == TEST_GPIO)
  GPIO_test();
  #elif (TEST_PERIPHERALS == TEST_TIMER)

  #endif

  while(1) {

  }

}
