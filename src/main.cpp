#include "nRF52core.h"

HardwareSerial Serial;

void setup() 
{
  Serial.begin(115200);
  pinMode(LED_1, OUTPUT);

}

void loop() {
  
  digitalToggle(LED_1);
  Serial.println(digitalRead(LED_1));
  nrf_delay_ms(500);
  
  //attachInterrupt(BUTTON_1, FALLING);

}

int main()
{
  
  setup();
  
  while(1) loop();
  
  
  
}
