# MicroUSB-B 5V input to 3.3V output
As part of learning electronics, i'm working on a custom PCB. This custom PCB decomposes an ESP32 DevBoard, reorders it and adds functionality. For this decomposition, I decided to isolate the power supply first.
As such, this custom PCB obtains the 5V input from a microUSB-B, and uses the AMS1117 Low-Dropout-Regulator (LDO) to get to a stable 3.3V. The PCB implements the original schematic from theorycircuit: https://theorycircuit.com/power-circuits/voltage-regulator-circuit-5v-to-3-3v/.

Image

## Shoppinglist for the components

| ID | Item | URL | Price (EUR) |
|-----|-----------|-----------|-----------|
|     1| Micro USB | https://www.distrelec.nl/nl/usb-connectoren-aansluiting-micro-usb-rechte-hoek-posities-wuerth-elektronik-629105150521/p/30009163 | 1.81 |    
|     2| AMS 1117 LDO | https://www.amazon.nl/dp/B019JV856Q?psc=1&ref=ppx_yo2ov_dt_b_product_details | 0.599 |
|     3| 220 &Omega; resistor, 10&mu;f capacitator, led | https://www.amazon.nl/gp/product/B08QGD9G7C | 0.017 |
