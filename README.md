Pinout Setup:


ESP8266 + ST7789:
|Screen|MCU|
| --- | --- |
|VCC: |  3v3 (You can use 5v, but the image seems more crisp and less blue with a slightly lower voltage on the Backlight) |
|GND: |  G |
|DIN/SDA: |  D7 |
|CLK/SCL: |  D5 |
|CS:  |  G (or D8) |
|DC:  |  D3 |
|RST/RES: |  D4 |
|BL:  |  3v3 (or D1 for dimming control) |


ESP32 + ILI9341
|Screen |  MCU  |
|  ---  |  ---  |
| T_IRQ |   27  |
| T_DO  |   19  |
| T_DIN |   23  |
| T_CS  |   21  |
| T_CLK |   18  |
|  SDO  |unused |
|  LED  |  3.3v |
|  SCK  |   18  |
|  SDI  |   23  |
|  DC   |   2   |
|  RST  |   4   |
|  CS   |   15  |
|  GND  |  GND  |
|  VCC  |  3.3v |
