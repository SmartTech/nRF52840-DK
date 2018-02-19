#include "nRF52core.h"

#include "nrf52_uart.h"

//HardwareSerial Serial1;

nrf_drv_uart_config_t uartConfig = NRF_DRV_UART_DEFAULT_CONFIG;

nrf_drv_uart_t uart0;

uint8_t rx_buffer[1];

void uart0_handler(nrf_drv_uart_event_t * p_event, void* p_context) {
  if (p_event->type == NRF_DRV_UART_EVT_RX_DONE)
  {
     // rx_buffer[0] = p_event->data.rxtx.p_data[0];
     // nrf_drv_uart_tx(&uart0, rx_buffer, 1);
  }
  else if (p_event->type == NRF_DRV_UART_EVT_ERROR)
  {
    
  }
  else if (p_event->type == NRF_DRV_UART_EVT_TX_DONE)
  {
     // nrf_drv_uart_rx(&uart0, rx_buffer, 1);
  }
}

uint8_t tx_buffer[1];

void setup()
{
  //Serial.begin(115200);
  pinMode(LED_1, OUTPUT);
  
  uartConfig.baudrate = NRF_UARTE_BAUDRATE_115200;
  uartConfig.pseltxd  = LINK_TX;
  uartConfig.pselrxd  = LINK_RX;
    
  uart0 = *getInstance(0);
  
  nrf_drv_uart_init(&uart0, &uartConfig, uart0_handler);
  
  // Turn on receiver if RX pin is connected
  if (uartConfig.pselrxd != 255) {
      if (!uartConfig.use_easy_dma) {
          nrf_drv_uart_rx_enable(&uart0);
      }
      nrf_drv_uart_rx(&uart0, rx_buffer, 1);
  }
  tx_buffer[0] = 0;
  
}


void loop() {
  
  digitalToggle(LED_1);
  //Serial.println(digitalRead(LED_1));
  nrf_delay_ms(200);
  nrf_drv_uart_tx(&uart0, tx_buffer, 1);
  tx_buffer[0]++;
  //attachInterrupt(BUTTON_1, FALLING);
  
  

}

int main()
{
  
  setup();
  
  //Serial.println("123");
  
  while(1) loop();
  
  
  
}
