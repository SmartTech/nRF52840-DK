#include "HardwareSerial.h"

HardwareSerial::HardwareSerial() :
  rx_pin(PIN_RX), tx_pin(PIN_TX), rts_pin(PIN_RTS), cts_pin(PIN_CTS), hfc(false)
{
  construct(0);
}

HardwareSerial::HardwareSerial(uint8_t _port, uint8_t _hfc) :
  rx_pin(PIN_RX), tx_pin(PIN_TX), rts_pin(PIN_RTS), cts_pin(PIN_CTS)
{
  construct(_port);
}

HardwareSerial::HardwareSerial(uint8_t _port, uint8_t _rx, uint8_t _tx, uint8_t _rts, uint8_t _cts, uint8_t _hfc) :
  rx_pin(_rx), tx_pin(_tx), rts_pin(_rts), cts_pin(_cts), hfc(_hfc)
{
  construct(_port);
}

void HardwareSerial::construct(uint8_t _port) {
  if(_port>1) return;
  config.pseltxd            = tx_pin;
  config.pselrxd            = rx_pin;
  config.pselcts            = cts_pin;
  config.pselrts            = rts_pin;
  config.p_context          = NULL;
  config.hwfc               = (nrf_uart_hwfc_t)hfc;
  config.parity             = (nrf_uart_parity_t)UART_DEFAULT_CONFIG_PARITY;
  config.baudrate           = (nrf_uart_baudrate_t)NRF_UART_BAUDRATE_115200;
  config.interrupt_priority = UART_DEFAULT_CONFIG_IRQ_PRIORITY;
  config.use_easy_dma       = true;
  //-----------------------------------------------
  if(_port==1) uart.p_uarte = NRF_UARTE1;
  else         uart.p_uarte = NRF_UARTE0;
  uart.drv_inst_idx = _port;
}

HardwareSerial::~HardwareSerial()
{
}

uint8_t HardwareSerial::begin(uint32 baud) {
  switch(baud) {
    case 1200    : config.baudrate = NRF_UART_BAUDRATE_1200;    break;
    case 2400    : config.baudrate = NRF_UART_BAUDRATE_2400;    break;
    case 4800    : config.baudrate = NRF_UART_BAUDRATE_4800;    break;
    case 9600    : config.baudrate = NRF_UART_BAUDRATE_9600;    break;
    case 14400   : config.baudrate = NRF_UART_BAUDRATE_14400;   break;
    case 19200   : config.baudrate = NRF_UART_BAUDRATE_19200;   break;
    case 28800   : config.baudrate = NRF_UART_BAUDRATE_28800;   break;
    case 38400   : config.baudrate = NRF_UART_BAUDRATE_38400;   break;
    case 57600   : config.baudrate = NRF_UART_BAUDRATE_57600;   break;
    case 76800   : config.baudrate = NRF_UART_BAUDRATE_76800;   break;
    case 115200  : config.baudrate = NRF_UART_BAUDRATE_115200;  break;
    case 230400  : config.baudrate = NRF_UART_BAUDRATE_230400;  break;
    case 250000  : config.baudrate = NRF_UART_BAUDRATE_250000;  break;
    case 460800  : config.baudrate = NRF_UART_BAUDRATE_460800;  break;
    case 921600  : config.baudrate = NRF_UART_BAUDRATE_921600;  break;
    case 1000000 : config.baudrate = NRF_UART_BAUDRATE_1000000; break;
    default: break;
  }
  
  //nrf_drv_uart_init(&uart, &config, &uart_my_handler);
    
  return NRF_SUCCESS;
  
}

void HardwareSerial::end(void) {
    nrf_drv_uart_uninit(&uart);
}

void HardwareSerial::uart_my_handler(nrf_uart_event_handler_t * p_event, void* p_context)
{
  
}

int HardwareSerial::read(void) {
    //if(usart_data_available(usart_device) > 0) {
    //        return usart_getc(usart_device);
    //} else {
            return -1;
    //}
}

int HardwareSerial::available(void) {
    //return usart_data_available(this->usart_device);
    return -1;
}

int HardwareSerial::peek(void)
{
    //return usart_peek(this->usart_device);
    return -1;
}

int HardwareSerial::availableForWrite(void)
{
  return 1;
}

size_t HardwareSerial::write(uint8_t txByte) {
  //const uint8_t txByte = (uint8_t)ch;
  static uint8_t tx_buffer[1];
  tx_buffer[0] = txByte;
  nrf_drv_uart_tx(&uart, tx_buffer, 1);
  return 1;
}

void HardwareSerial::flush(void) {
    //while(!rb_is_empty(this->usart_device->wb)); // wait for TX buffer empty
    //while(!((this->usart_device->regs->SR) & (1<<USART_SR_TC_BIT))); // wait for TC (Transmission Complete) flag set 
}
