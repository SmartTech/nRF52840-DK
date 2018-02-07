// GPIO abstraction Reference:
// http://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.nrf52%2Fdita%2Fnrf52%2Fcompatibility_matrix%2FnRF52840_doc_ref_design_files_overview.html

// Реализация в файле: nrf_gpio.h

// NRF_GPIO_PIN_MAP(port, pin) // макрос преобразования в цифровой номер пина

// Конфигурации работы вход/выход
// enum	nrf_gpio_pin_dir_t {
//   NRF_GPIO_PIN_DIR_INPUT = GPIO_PIN_CNF_DIR_Input,
//   NRF_GPIO_PIN_DIR_OUTPUT = GPIO_PIN_CNF_DIR_Output
// }

// Конфигурации подключения входного буфера
// enum	nrf_gpio_pin_input_t {
//   NRF_GPIO_PIN_INPUT_CONNECT = GPIO_PIN_CNF_INPUT_Connect,
//   NRF_GPIO_PIN_INPUT_DISCONNECT = GPIO_PIN_CNF_INPUT_Disconnect
// }

// Конфигурации подтяжек
// enum  	nrf_gpio_pin_pull_t {
//   NRF_GPIO_PIN_NOPULL   = GPIO_PIN_CNF_PULL_Disabled,
//   NRF_GPIO_PIN_PULLDOWN = GPIO_PIN_CNF_PULL_Pulldown,
//   NRF_GPIO_PIN_PULLUP   = GPIO_PIN_CNF_PULL_Pullup
// }

// Конфигурации определения уровня пина на вход
// enum  	nrf_gpio_pin_sense_t {
//   NRF_GPIO_PIN_NOSENSE    = GPIO_PIN_CNF_SENSE_Disabled,
//   NRF_GPIO_PIN_SENSE_LOW  = GPIO_PIN_CNF_SENSE_Low,
//   NRF_GPIO_PIN_SENSE_HIGH = GPIO_PIN_CNF_SENSE_High
// }

// void nrf_gpio_cfg	(	uint32_t 	            pin_number, // номер пина
//                     nrf_gpio_pin_dir_t 	  dir,        // направление пина вход/выход
//                     nrf_gpio_pin_input_t 	input,      // подклбючение входного буфера Connect / Disconnect
//                     nrf_gpio_pin_pull_t 	  pull,       // настройка подтяжки
//                     nrf_gpio_pin_drive_t 	drive,      // режим управления выходом
//                     nrf_gpio_pin_sense_t 	sense       // режим определения входного уровня
//                     )

// Конфигурации режима управления пином вход/выход, использующие функцию nrf_gpio_cfg
// nrf_gpio_cfg_input (uint32_t pin_number, nrf_gpio_pin_pull_t pull_config)
// nrf_gpio_cfg_output (uint32_t pin_number)
// nrf_gpio_cfg_sense_input (uint32_t pin_number, nrf_gpio_pin_pull_t pull_config, nrf_gpio_pin_sense_t sense_config)

// Note: нет готовых функций для настройки режим управления выходом,
//       следует сделать функцию nrf_gpio_cfg_drive(nrf_gpio_pin_drive_t drive)
//       Для удобства настройки реализовать pinMode(pon, mode_t), где:
//       enum mode_t {
//         INPUT = 0,
//         INPUT_PULLUP,
//         INPUT_PULLDOWN,
//         OUTPUT,
//         OUTPUT_OD
//       }

// Управление пинами:
// nrf_gpio_pin_write    (uint32_t pin_number, uint32_t value) // установить состояние выходного пина
// nrf_gpio_pin_clear    (uint32_t pin_number)                 // установить выходной пин в LOW
// nrf_gpio_pin_set      (uint32_t pin_number)                 // установить выходной пин в HIGH
// nrf_gpio_pin_toggle   (uint32_t pin_number)                 // инвертировать состояние выходного пина
// nrf_gpio_pin_read     (uint32_t pin_number)                 // чтение пина настроенного на вход
// nrf_gpio_pin_out_read (uint32_t pin_number)                 // чтение пина настроенного на выход

//----------------------------------------------------------------------------------------------------
// Следующие реализации только для PlatformIO:
// -------------------------------------------
// Подключение объектов класса управления пинами:
// AnalogIn(PinName pin)
// AnalogOut(PinName pin)
// DigitalIn(PinName pin)
// DigitalIn(PinName pin, PinMode mode)
// DigitalOut(PinName pin)
// DigitalOut(PinName pin, int value)
// DigitalInOut(PinName pin)
// DigitalInOut(PinName pin, PinDirection direction, PinMode mode, int value)
// Прерывания
// InterruptIn(PinName pin)
//

// Note: PinMode - настройка подтяжки
//       PinNames.h - файл с энумерацией пинов
//       путь к файлу: "..\framework-mbed\targets\TARGET_NORDIC\TARGET_NRF5\TARGET_MCU_NRF52840\TARGET_NRF52840_DK"

// Пример использования:
// DigitalOut myLed[4] = {(LED1),(LED2),(LED3),(LED4)};
// DigitalIn  myBtn[4] = {(BUTTON1),(BUTTON2),(BUTTON3),(BUTTON4)};
