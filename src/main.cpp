

#ifdef IS_PLATFORM_IO
#include <mbed.h>
#include "PlatformIO_test/GPIO.h"
#else
#include "MBED_test/GPIO.h"
#endif

#include "config.h"

int main() {

  #if (TEST_PERIPHERALS == TEST_GPIO)
  GPIO_test();
  #elif (TEST_PERIPHERALS == TEST_TIMER)

  #endif

  while(1) {

  }

}
