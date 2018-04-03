# Overview

This project aims to create an easy to use usb interface to control an STM32F103C8 (blue pill). It has the ability to read and write the GPIO pins, read the ADC pins and return the voltage (12 bit resolution), and control the pwm outputs (up to 16 bit resolution and between 1 Hz - 250 kHz frequency).

# Drivers

WINDOWS
  * To use this device on windows you will need to download the stm32 Virtual COM Port Driver (http://www.st.com/en/development-tools/stsw-stm32102.html)
  * After the driver is installed the device will show up as a com port.
  
LINUX
  * To us this device on Linux you will need the ttyACM drivers enabled in the kernel. This driver is usually enabled by default.
  * The device will show up in /dev as a ttyACM device

# Flashing STM32F103C8

1. The bin file to load onto the STM32F103C8 is located in the releases folder.
2. The STM32F103C8 can be flashed with multiple different methods. There is an excelent tutorial on how to do that here http://wiki.stm32duino.com/index.php?title=Burning_the_bootloader

# HOW-TO

GPIO
  1. Enable a GPIO pin. INITIALIZE GPIO [PIN] [IN|OUT] [NOPULL|PULLUP|PULLDOWN]
      * The STM32F103C8 has many available gpio pins that can be configured as either an output or an input with a pullup or pulldown or floating. A0-A15, B0-B15, C13-C15
      * Some pins should not be used as they performing critical functions. Pins A11 and A12 are being used for the USB port. Pins C14 and C15 are being used for the crystal oscilator.
  2. Set a GPIO pin. SET GPIO [PIN] [VALUE]
      * The pin must first be initialized as an output.
      * The value can be set to 0, L, LOW, F, or FALSE for a low value and 1, H, HIGH, T, or TRUE for a high value.
  3. Read a GPIO pin. READ GPIO [PIN]
      * The value returned is a 1 for a high value and 0 for a low value.
      * Multiple pins can be read in 1 command by sending READ GPIO [PIN] [PIN] [PIN] ...

ADC
  1. Enable an ADC pin. INITIALIZE ADC [PIN] [CONVERSION TIME]
      * The available ADC pins are A0-A7 and B0-B1.
      * Conversion time is optional, the available conversion times are 0.125us, 0.625us, 1.125us, 2.375us, 3.458us, 4.625us, 5.958us and 19.96us. 0.125us is chosen if no conversion time is selected.
  2. Read an ADC pin. READ ADC [PIN]
      * The pin must first be initialized as an ADC pin.
      * The value returned is between 0V and 3.3V.
      * Multiple pins can be read in 1 command by sending READ ADC [PIN] [PIN] [PIN] ...
      
PWM
  1. Enabled a PWM channel. INITIALIZE PWM CHANNEL [CHANNEL] [FREQUENCY]
      * The STM32F103C8 has 4 different PWM channels. Each channel can control up to 4 PWM outputs. Each channel has a set frequency for its PWM outputs
  2. Enable a PWM pin. INITIALIZE PWM PIN [PIN]
      * Available Channels-Pin. 
          * Channel 1 - A8, A9, A10
          * Channel 2 - A0, A1, A2, A3
          * Channel 3 - A6, A7, B0, B1
          * Channel 4 - B6, B7, B8, B9
  3. Set a PWM pin. SET PWM [PIN] [DUTY CYCLE 0.000000-1.000000]
      * The pin must first be initialized as a PWM pin.
      * Duty cycle represented between 0.000000 for always low to 1.000000 for always high.
      
Turn off response messages
  1. It is sometimes necessary to disable the response messages so as not to interfere with READ ADC and READ GPIO. This can be done by sending DISABLE RESPONSES
  2. To re-enable responses, send ENABLE RESPONSES
