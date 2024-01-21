# Pandoras box

Pandoras box started as a hobby project to teach myself the basics of hardware security. The PCB requires the ESP32 and various other components to function well. If offers the following hardware security learnings:

* Identifying UART PINS and 'sniffing' them;
* Identifying I2C PINS and 'sniffing' them;
* Taking off the external EEPROM and reading its external memory;
* Dumping the ESP32 firwmare to identify board information;
* A basic timing attack against the PIN protection.

Note: you need to manually set the password on the EEPROM at address 1

## Getting Started

### Hardware 
To order the board, you need to convert the <a href="https://github.com/JeroenSlobbe/Hardware/tree/main/Pandoras%20box/KICAD%20design/1.0">KICAD design files</a> to Gerber files. This can be done in KICAD by opening the PCB editor and by clicking: File -> Fabrication outputs -> Gerbers (.gbs) -> Plot + Generate drill files. After zipping these files, you can upload them to <a href="https://jlcpcb.com/"> JLCPCB </a> (or your favority PCB manufacturer) and place your order.

#### Shoppinglist for the box itself

| ID | Item | URL |
|-----:|-----------|-----------|
|     1| EEPROM    |https://www.amazon.nl/Reland-Sun-24LC16B-I-24LC128-I-24LC512-I/dp/B09JJSLCLR|
|     2| ESP32    |https://www.amazon.nl/gp/product/B071P98VTG/|
|     3| LED, 4x4 membrane, resistors| https://www.amazon.nl/ELEGOO-Complete-Ultimate-Gebruiken-Controller/dp/B01II76PDM|
|     4| USB 2 Micro-USB    |https://www.amazon.nl/gp/product/B07NSMG2QQ|
|     5| PIN headers      |https://www.amazon.nl/dp/B07XXXNH9V |
|     5| Horizontal PIN headers     | https://www.amazon.nl/dp/B07CWSXY7P |

####  Shoppinglist to assemble the box

| ID | Item | URL |
|-----:|-----------|-----------|
|     1| Soldering iron    |https://www.amazon.nl/dp/B0BS1MD3NC|
|     2| Soldering tin    | https://www.amazon.nl/dp/B0C3GQ8Y7V|


#### Shoppinglist for experiencing the attacks

| ID | Item | URL |
|-----:|-----------|-----------|
|     1| Picoscope    |https://www.picotech.com/oscilloscope/2000/picoscope-2000-overview|
|     2| Multimeter    |https://www.amazon.nl/dp/B09K5DMTQ3|
|     3| Logic analyser| https://www.amazon.nl/gp/product/B07D21GG6J|
|     4| USB 2 TTL | https://www.amazon.nl/dp/B089QJZ51Z|


### Software

* Arduino IDE: https://www.arduino.cc/en/software
  ```
  File -> Preferences -> Additional board Manager URL -> https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
  Tools -> Board -> Board Manager -> esp32/Espressif Systems version 2.0.11
  keypad libary by Mark Stanly and Alexander Brevig
  ```
* PCB design software KICAD: https://www.kicad.org/download/
* Picoscope software: https://www.picotech.com/downloads
  ```
  CMD.exe -> SystemPropertiesAdvanced -> 'Environment Variables' -> PATH -> [add path of pico installation: c:\program files\pico technology\PicoScope 7 T&M Stable]
  reboot
  ```
* Putty: https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html
* Python3
  ```
  pip install picosdk
  pip install esptool
  ```

### Roadmap
- [ ] KICAD: Standardize the PCB support holes distance (e.g. same distance for all 4 corner holes between the edged of the board)  
- [ ] KICAD: Standardize the PCB support holes diameter (e.g. radius of 2.5mm instead of 2.54mm)
- [ ] KICAD: Use TXD and RXD for UART communication, freeing up GPIO18 and GPIO19 for other purposes
- [ ] KICAD: Add GPIO numbering to silk
- [ ] KICAD: Add MicroSD card mount / resistors to board and connect to GPIO 17, GPIO16 , GPIO 18, GPIO19
- [ ] KICAD: Add pins for SPI sniffing (CS, MOSI, MISO, CLK)
- [ ] KICAD: Add button(s) for initiating SPI/UART/I2C reading
- [ ] KICAD: See if SMD resistors can be used, to safe space and let the board look more slick
- [x] ARDUINO: Implement WiFi AP so users can connect to Pandoras box
- [ ] ARDUINO: Implement Webserver so users can read about pandoras box (files should be obtained via the SD-CARD)
- [ ] ARDUINO: Implement buttons for initaiting the communication
- [ ] ARDUINO: rewrite all code to work in Eclise and follows the full ESP-IDF compilitaion process to increase control over bootloader / application
- [ ] 3D: add ornaments to make the box look more fancy
- [ ] 3D: Create a lid to enusre the box can be closed
- [ ] 3D: Move ESP32 mouth to right to improve allignment
- [ ] HTML: Write tutorials for various attacks & defenses
- [ ] HTML: Obtain copy of MITTRE-EMB3D and map tutorial to this framework
- [ ] PYTHON: Write exploit for if only flash encryption is enabled
- [ ] VULNERABILITY: Create vulnerable RSA functionality
- [ ] VULNERABILITY: Create a computation in which glitching is easy and visible
- [ ] VULNERABILITY: ARDUINO: Downgrade WPA2 to WPA or WEP https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html#_CPPv416wifi_auth_mode_t
- [ ] VULNERABILITY: Look for inspiration:
* https://i.blackhat.com/USA-22/Wednesday/US-22-ABDELLATIF-Unlimited-Results-Breaking-Firmware-Encryption.pdf
* https://www.slideshare.net/ssuser6e61b3/eu19limitedresultsfatalfuryonesp32timetoreleasehardwareexploitspdf
* https://rtfm.newae.com/Capture/ChipWhisperer-Nano/
* https://ryancor.medium.com/pulling-bits-from-rom-silicon-die-images-unknown-architecture-b73b6b0d4e5d
- [ ] GENERAL: see if ESP32-devboard can be decomposed to make board-layout more compelling


<!-- CONTACT -->
## Contact

Jeroen Slobbe - [@JeroenSlobbe](https://twitter.com/JeroenSlobbe) -

<p align="right">(<a href="#readme-top">back to top</a>)</p>
