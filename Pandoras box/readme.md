Pandoras box started as a hobby project to teach myself the basics of hardware security. The PCB requires the ESP32 and various other components to function well. If offers the following hardware security learnings:

* Identifying UART PINS and 'sniffing' them;
* Identifying I2C PINS and 'sniffing' them;
* Taking off the external EEPROM and reading its external memory;
* Dumping the ESP32 firwmare to identify board information;
* A basic timing attack against the PIN protection.

Note: you need to manually set the password on the EEPROM at address 1

## Shoppinglist for Pandoras box

EEPROM: https://www.amazon.nl/Reland-Sun-24LC16B-I-24LC128-I-24LC512-I/dp/B09JJSLCLR?th=1
ESP32: https://www.amazon.nl/gp/product/B071P98VTG/
LEDs, 4x4 membrane, resistors: https://www.amazon.nl/ELEGOO-Complete-Ultimate-Gebruiken-Controller/dp/B01II76PDM
USB - Micro USB: https://www.amazon.nl/gp/product/B07NSMG2QQ


Soldering iron: https://www.amazon.nl/dp/B0BS1MD3NC?psc=1&ref=ppx_yo2ov_dt_b_product_details
Soldering tin: https://www.amazon.nl/dp/B0C3GQ8Y7V?psc=1&ref=ppx_yo2ov_dt_b_product_details

## Shoppinglist for experiencing the attacks

PicoScope: https://www.picotech.com/oscilloscope/2000/picoscope-2000-overview
Multimeter: https://www.amazon.nl/dp/B09K5DMTQ3
Logic analyser: https://www.amazon.nl/gp/product/B07D21GG6J
