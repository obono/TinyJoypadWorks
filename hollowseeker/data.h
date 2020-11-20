#pragma once

/*---------------------------------------------------------------------------*/
/*                                 Image Data                                */
/*---------------------------------------------------------------------------*/

PROGMEM static const uint8_t imgPlayer[][8] = { // 8x8 x8
    { 0x10, 0x83, 0xAC, 0x69, 0x6D, 0xAD, 0x82, 0x10 }, // left 0
    { 0x00, 0x13, 0x6C, 0x69, 0xED, 0xAD, 0x02, 0x20 }, // left 1
    { 0x00, 0x23, 0x2C, 0xE9, 0xED, 0x2D, 0x02, 0x20 }, // left 2
    { 0x20, 0x06, 0xD8, 0xD2, 0x5A, 0x5A, 0xC4, 0x10 }, // left 3
    { 0x10, 0x82, 0xAD, 0x6D, 0x69, 0xAC, 0x83, 0x10 }, // right 0
    { 0x20, 0x02, 0xAD, 0xED, 0x69, 0x6C, 0x13, 0x00 }, // right 1
    { 0x20, 0x02, 0x2D, 0xED, 0xE9, 0x2C, 0x23, 0x00 }, // right 2
    { 0x10, 0xC4, 0x5A, 0x5A, 0xD2, 0xD8, 0x06, 0x20 }, // right 3
};

PROGMEM static const uint8_t imgCave[] = { // 8x8
    0x90, 0x06, 0x4E, 0xE4, 0xC0, 0x88, 0x18, 0x99
};

#define IMG_READY_W     50
#define IMG_READY_H     16

PROGMEM static const uint8_t imgReady[100] = { // "Ready?" 50x16
    0x00, 0x00, 0xF8, 0xF8, 0xF8, 0x98, 0xF8, 0xF8, 0x70, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0,
    0xC0, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xF8,
    0xF8, 0xF8, 0x40, 0xC0, 0xC0, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x38, 0x98, 0xD8, 0xF8, 0xF8, 0x70,
    0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x01, 0x1F, 0x1E, 0x18, 0x00, 0x07, 0x0F, 0x1F, 0x1A,
    0x1A, 0x1B, 0x1B, 0x03, 0x0C, 0x1E, 0x1E, 0x1A, 0x1F, 0x1F, 0x1F, 0x00, 0x0F, 0x1F, 0x1F, 0x18,
    0x08, 0x1F, 0x1F, 0x1F, 0xC0, 0xC1, 0xCF, 0xFF, 0x7C, 0x1F, 0x03, 0x00, 0x00, 0x1D, 0x1D, 0x1D,
    0x00, 0x00, 0x00, 0x00
};


#define IMG_GAMEOVER_W  78
#define IMG_GAMEOVER_H  16

PROGMEM static const uint8_t imgGameOver[156] = { // "Game Over" 78x16
    0x00, 0x00, 0xC0, 0xF0, 0xF0, 0x38, 0x98, 0x98, 0x98, 0xB8, 0x80, 0x00, 0x00, 0xC0, 0xC0, 0xC0,
    0xC0, 0xC0, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00,
    0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF0, 0x38, 0x18,
    0x18, 0x38, 0xF0, 0xF0, 0xC0, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xC0, 0xC0, 0x40, 0x00, 0x80,
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x0F, 0x0F, 0x1C, 0x19, 0x19, 0x1F, 0x1F, 0x0F, 0x00, 0x0C, 0x1E, 0x1E, 0x1A, 0x1F, 0x1F,
    0x1F, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x07, 0x0F,
    0x1F, 0x1A, 0x1A, 0x1B, 0x1B, 0x03, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x0F, 0x1C, 0x18, 0x18, 0x1C,
    0x0F, 0x0F, 0x03, 0x00, 0x00, 0x07, 0x1F, 0x1F, 0x1E, 0x1F, 0x03, 0x00, 0x07, 0x0F, 0x1F, 0x1A,
    0x1A, 0x1B, 0x1B, 0x03, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00
};

#define IMG_FIGURE_W    8
#define IMG_FIGURE_H    8

PROGMEM static const uint8_t imgFigure[][8] = { // 8x8 x10
    { 0x3C, 0x7E, 0x43, 0x41, 0x61, 0x7F, 0x3E, 0x00 },
    { 0x00, 0x02, 0x02, 0x7F, 0x7F, 0x00, 0x00, 0x00 },
    { 0x42, 0x63, 0x71, 0x51, 0x59, 0x4F, 0x4E, 0x00 },
    { 0x32, 0x73, 0x41, 0x49, 0x69, 0x7F, 0x36, 0x00 },
    { 0x30, 0x28, 0x24, 0x22, 0x7F, 0x7F, 0x20, 0x00 },
    { 0x0E, 0x4F, 0x49, 0x49, 0x69, 0x79, 0x31, 0x00 },
    { 0x3C, 0x7E, 0x4B, 0x49, 0x69, 0x78, 0x30, 0x00 },
    { 0x02, 0x03, 0x01, 0x71, 0x7D, 0x0F, 0x03, 0x00 },
    { 0x36, 0x7F, 0x49, 0x49, 0x6D, 0x7F, 0x36, 0x00 },
    { 0x06, 0x4F, 0x49, 0x49, 0x69, 0x7F, 0x3E, 0x00 }
};

/*---------------------------------------------------------------------------*/
/*                                 Sound Data                                */
/*---------------------------------------------------------------------------*/

PROGMEM static const uint8_t soundStart[] = {
    72, 12, 74, 12, 76, 12, 77, 12, 79, 36, 0xFF
};

PROGMEM static const uint8_t soundOver[] = {
    55, 13, 54, 16, 53, 19, 52, 22, 51, 25, 50, 28, 49, 31, 48, 34, 0xFF
};
