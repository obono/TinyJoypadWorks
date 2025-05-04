# TinyJoypadWorks [![CircleCI Build Status](https://circleci.com/gh/obono/TinyJoypadWorks.svg?style=shield)](https://circleci.com/gh/obono/TinyJoypadWorks) ![MIT Licensed](https://img.shields.io/badge/license-MIT-blue.svg)

Making mini games for [TinyJoypad](https://www.tinyjoypad.com/tinyjoypad_attiny85).

## Products

* OBN-T00 [Test tool](https://raw.githubusercontent.com/obono/TinyJoypadWorks/main/_hexs/testtool_v0.5.hex)
  * Version 0.5 (updated on November 17, 2020)
  * For operation confirmation.\
    ![screenshot](testtool/preview/1_top.gif) ![screenshot](testtool/preview/2_button.gif) ![screenshot](testtool/preview/3_character.gif)
* OBN-T01 [Hollow Seeker](https://raw.githubusercontent.com/obono/TinyJoypadWorks/main/_hexs/hollowseeker_v0.1.hex)
  * Version 0.1 (released on Novemver 20, 2020)
  * Go forward in right direction. Seek a hollow as refuge not to be crushed.\
    ![screenshot](hollowseeker/preview/1_title.gif) ![screenshot](hollowseeker/preview/2_playing.gif) ![screenshot](hollowseeker/preview/3_playing.gif)
* OBN-T02 [Number Place](https://raw.githubusercontent.com/obono/TinyJoypadWorks/main/_hexs/numberplace_v0.3.hex)
  * Version 0.3 (released on January 10, 2021)
  * A logic-based, combinatorial number-placement puzzle.\
    ![screenshot](numberplace/preview/1_title.gif) ![screenshot](numberplace/preview/2_start.gif) ![screenshot](numberplace/preview/3_complete.gif)
* OBN-T03 [2048](https://raw.githubusercontent.com/obono/TinyJoypadWorks/main/_hexs/t2048_v0.1.hex)
  * Version 0.1 (released on May 4, 2025)
  * Join the tiles, get to 2048.\
    ![screenshot](t2048/preview/1_title.gif) ![screenshot](t2048/preview/2_playing.gif) ![screenshot](t2048/preview/3_playing.gif)

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
