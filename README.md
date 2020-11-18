# TinyJoypadWorks [![CircleCI Build Status](https://circleci.com/gh/obono/TinyJoypadWorks.svg?style=shield)](https://circleci.com/gh/obono/TinyJoypadWorks) ![MIT Licensed](https://img.shields.io/badge/license-MIT-blue.svg)

Making mini games for [TinyJoypad](https://www.tinyjoypad.com/tinyjoypad_attiny85).

## Products

* OBN-T00 [Test tool](https://raw.githubusercontent.com/obono/TinyJoypadWorks/main/_hexs/testtool_v0.5.hex)
  * Version 0.5 (released on Novemver 2, 2020)
  * For operation confirmation.\
    ![screenshot](testtool/preview/1_top.gif) ![screenshot](testtool/preview/2_button.gif) ![screenshot](testtool/preview/3_character.gif)

## Build enviroment

[Install ATTinyCore boards to the Arduino IDE](https://github.com/SpenceKonde/ATTinyCore/blob/master/Installation.md) and configure the settings as follows.

Attribute        |Value
-----------------|------------------------------
Board            |ATtiny25/45/85 (No bootloader)
Chip             |ATtiny85
Clock            |16 MHz (PLL)
B.O.D. Level     |B.O.D. Disabled (saves power)
Save EEPROM      |EEPROM retained
Timer 1 Clock    |CPU (CPU frequency)
LTO              |Enabled
millis()/micros()|Enabled

## Acknowledgement

* [SimpleWire.h](https://lab.sasapea.mydns.jp/2020/03/11/avr-i2c-2/)
  * Copyright (c) 2020 Sasapea's Lab. All right reserved.

## License

These codes are licensed under [MIT License](LICENSE).
