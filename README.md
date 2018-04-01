# Overview

This project aims to create an easy to use usb interface to control an STM32F103C8 (blue pill). It has the ability to read and write the GPIO pins, read the ADC pins and return the voltage (12 bit resolution), and control the pwm outputs (up to 16 bit resolution and between 1 - 250 khz frequency).

# Drivers

1. WINDOWS
  a. To use this device on windows you will need to download the stm32 Virtual COM Port Driver (http://www.st.com/en/development-tools/stsw-stm32102.html)
  b. After the driver is installed the device will show up as a com port.
  
1. LINUX
  a. To us this device on Linux you will need the ttyACM drivers enabled in the kernel. This driver is usually enabled by default.
  b. The device will show up in /dev as a ttyACM device
  
# HOW-TO

GPIO
  1. Enable the GPIO pin.
      a. The STM32F103C8 has many available gpio pins, however some pins should not be used as they performing critical functions. Pins A11 and A12 are being used for the USB port. Pins C14 and C15(Not available on the blue pill) are being used for the crystal oscilator.
