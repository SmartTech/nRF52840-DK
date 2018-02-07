# nRF52840-DK
Проект использования MBED фрэймворка на PlatformIO
 - Включает настроеный проект для IAR

[Markdown](https://guides.github.com/features/mastering-markdown/) - синтаксис MD файлов

# Документация
### [Datasheet](https://github.com/SmartTech/nRF52840-DK/blob/master/Doc/nRF52840/nRF52840_OPS_v0.5.pdf)
### [Основные функции MBED фреймворка](https://github.com/SmartTech/nRF52840-DK/tree/master/Doc/MBED)
- [GPIO](https://github.com/SmartTech/nRF52840-DK/blob/master/Doc/MBED/GPIO.h)
- [ADC](https://github.com/SmartTech/nRF52840-DK/blob/master/Doc/MBED/ADC.h)

# Примеры
### [PlatformIO](https://github.com/SmartTech/nRF52840-DK/tree/master/src/PlatformIO_test)
- [GPIO](https://github.com/SmartTech/nRF52840-DK/blob/master/src/PlatformIO_test/GPIO.h)
### [IAR](https://github.com/SmartTech/nRF52840-DK/tree/master/src/MBED_test)
- [GPIO](https://github.com/SmartTech/nRF52840-DK/blob/master/src/MBED_test/GPIO.h)

# HowTo
В файле config.h настроить объявления:
> //#define IS_PLATFORM_IO // раскомментировать для сборки на PlatformIO

> #define TEST_PERIPHERALS   TEST_GPIO // выбор теста для компиляции

Наименования тестов:
- TEST_GPIO
- TEST_TIMER

# Отладочная плата
![Image of Yaktocat](https://github.com/SmartTech/nRF52840-DK/blob/master/Doc/nRF52840-DK.png)
