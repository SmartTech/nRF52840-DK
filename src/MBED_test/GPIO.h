#ifndef _GPIO_H
#define _GPIO_H

#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

void GPIO_handle(void);

// Объявление пина
#define LED_1      NRF_GPIO_PIN_MAP(0,13)
#define LED_2      NRF_GPIO_PIN_MAP(0,14)
#define LED_3      NRF_GPIO_PIN_MAP(0,15)
#define LED_4      NRF_GPIO_PIN_MAP(0,16)

//#define BUTTON_1   NRF_GPIO_PIN_MAP(0,11)
//#define BUTTON_2   NRF_GPIO_PIN_MAP(0,12)
//#define BUTTON_3   NRF_GPIO_PIN_MAP(0,24)
//#define BUTTON_4   NRF_GPIO_PIN_MAP(0,25)

void GPIO_test() {

  nrf_gpio_cfg_input(BUTTON_1, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON_2, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON_3, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON_4, NRF_GPIO_PIN_PULLUP);

  nrf_gpio_cfg_output(LED_1);
  nrf_gpio_cfg_output(LED_2);
  nrf_gpio_cfg_output(LED_3);
  nrf_gpio_cfg_output(LED_4);

  while(1) {
    GPIO_handle();
  }

}

void GPIO_handle() {

  nrf_gpio_pin_write(LED_1, nrf_gpio_pin_read(BUTTON_1));
  nrf_gpio_pin_write(LED_2, nrf_gpio_pin_read(BUTTON_2));
  nrf_gpio_pin_write(LED_3, nrf_gpio_pin_read(BUTTON_3));
  nrf_gpio_pin_write(LED_4, nrf_gpio_pin_read(BUTTON_4));

  nrf_delay_ms(1);

}

#endif // _GPIO_H
