# MicroUSB-B 5V input to 3.3V output
As part of learning electronics, i'm working on a custom PCB. This custom PCB decomposes an ESP32 DevBoard, reorders it and adds functionality. For this decomposition, I decided to isolate the power supply first. As such, this custom PCB obtains the 5V input from a microUSB-B, and uses the AMS1117 Low-Dropout-Regulator (LDO) to get to a stable 3.3V. The PCB implements the original schematic from [theorycircuit](https://theorycircuit.com/power-circuits/voltage-regulator-circuit-5v-to-3-3v/):

![Original circuit](https://github.com/JeroenSlobbe/Hardware/blob/main/MicroUSB_5V_to_3.3V/img/circuit.png?raw=true)


## Shoppinglist for the components
Components to buy:
| ID | Item | URL | Price (EUR) |
|-----|-----------|-----------|-----------|
|     1| Micro USB | https://www.distrelec.nl/nl/usb-connectoren-aansluiting-micro-usb-rechte-hoek-posities-wuerth-elektronik-629105150521/p/30009163 | 1.81 |    
|     2| AMS 1117 LDO | https://www.amazon.nl/dp/B019JV856Q?psc=1&ref=ppx_yo2ov_dt_b_product_details | 0.599 |
|     3| 220 &Omega; resistor, 10&mu;f capacitator, led | https://www.amazon.nl/gp/product/B08QGD9G7C | 0.017 |


# Design decissions & Improvements

- [x] Decission: to use a [via](https://en.wikipedia.org/wiki/Via_(electronics)) to connect the AMS1117 3.3V output towards the pin. Although it would be possible to wire it, such that no wires overlap, I wanted to use a via for educational purposes;
- [ ] Improvement: redo wiring, so that the ground and vcc input don't need to cross within the microUSB footprint;
- [x] Improvement: add VCC, GND and PWR_FLAG symbols, as well as the NO_CONNECT flag for pins of the USB not being used;
- [ ] Improvement: calculate precise track size according to the IPC-2152 standard / as described [in this article](https://www.studiopieters.nl/track/).

The end result: 

![Resulting PCB](https://github.com/JeroenSlobbe/Hardware/blob/main/MicroUSB_5V_to_3.3V/img/PCB.png?raw=true)
