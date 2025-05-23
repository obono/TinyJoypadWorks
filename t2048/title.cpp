#include "common.h"

/*  Defines  */

#define IMG_TITLE_W 80
#define IMG_TITLE_H 24

/*  Local Constants  */

PROGMEM static const uint8_t imgTitle[] = { // 80x24
    0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0x7E, 0x3E, 0x3E, 0x3E, 0x3E, 0x7E, 0xFE, 0xFC, 0xFC, 0xF8,
    0xF0, 0xE0, 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0x3E, 0x1E, 0x1E, 0x1E, 0x1E, 0x3E,
    0xFE, 0xFC, 0xFC, 0xF8, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF0,
    0xF8, 0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0,
    0xF8, 0xFC, 0xFC, 0xFE, 0x3E, 0x1E, 0x1E, 0x1E, 0x1E, 0x3E, 0xFE, 0xFC, 0xFC, 0xF8, 0xF0, 0x00,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0x7F, 0x3F, 0x1F, 0x0F,
    0x07, 0x03, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xE0, 0xF0, 0xF8, 0xFE, 0xFF, 0xFF, 0xDF, 0xC7,
    0xC3, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xC0, 0xE3,
    0xF7, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x3C, 0x3C, 0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xF7, 0xE3, 0xC0,
    0x70, 0x78, 0x7C, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7B, 0x79, 0x78, 0x78, 0x78, 0x78, 0x78,
    0x78, 0x78, 0x00, 0x00, 0x03, 0x0F, 0x1F, 0x3F, 0x3F, 0x7F, 0x7C, 0x78, 0x78, 0x78, 0x78, 0x7C,
    0x7F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x0F, 0x1F,
    0x3F, 0x3F, 0x7F, 0x7F, 0x7C, 0x78, 0x78, 0x78, 0x78, 0x7C, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x0F
};

/*  Local Variables  */

void initTitle(void)
{
    setSprite(0, 24, 16, imgTitle, IMG_TITLE_W, IMG_TITLE_H, WHITE);
    setString(8, 31, F("PRESS BUTTON"), WHITE);
    isInvalid = true;
}

MODE_T updateTitle(void)
{
    randomSeed(rand()); // Shuffle random
    return (isButtonDown(A_BUTTON)) ? MODE_GAME : MODE_TITLE;
}
