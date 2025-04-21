# Filament Dryer Controller
## Overview
## Details
something something filament something something dry
### Processor
- ATMega328P
### Inputs
#### Button
- Pin D2
- Momentary
- Internal pull-up
#### PTC thermistor
- Pin A0
- B3950
- 100KΩ @25°C
- B-value 3950 @50°C
- 100KΩ external pull-down
#### Temperature & humudity sensor
- I2C 0x44
- SHT30-D
### Outputs
#### Ok LED
- Pin D12
- Yellow
#### Heating LED
- Pin D13
- Red
#### Display
- I2C 0x78
- 128X64 Monochrome OLED
- SH1106
