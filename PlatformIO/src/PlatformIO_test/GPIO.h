#ifndef _GPIO_H
#define _GPIO_H

#include <mbed.h>
#include "nrf_delay.h"
#include "InterruptManager.h"

DigitalOut  GPIO_Led[4] = {(LED1),(LED2),(LED3),(LED4)};
DigitalIn   GPIO_Btn[4] = {(BUTTON1),(BUTTON2),(BUTTON3),(BUTTON4)};

InterruptIn GPIO_eventFalling(BUTTON1);
InterruptIn GPIO_eventRising(BUTTON2);

Ticker flipper;

void GPIO_flip(void) {
  GPIO_Led[2] = !GPIO_Led[2];
}

void GPIO_Timer_handler(void) {
  GPIO_Led[3] = !GPIO_Led[3];
}

void GPIO_triggerRising() {
  GPIO_Led[1] = !GPIO_Led[1];
}

void GPIO_triggerFalling() {
  GPIO_Led[0] = !GPIO_Led[0];
}

void GPIO_test() {

  GPIO_Led[1] = GPIO_Led[2] = 0;
  GPIO_eventRising.rise(&GPIO_triggerRising);
  GPIO_eventFalling.fall(&GPIO_triggerFalling);
  flipper.attach(&GPIO_flip, 1.0);
  InterruptManager::get()->add_handler(GPIO_Timer_handler, TIMER3_IRQn);

  while(1) {
    wait_ms(1);
    //nrf_delay_ms(1);
  }

}

#endif // _GPIO_H
