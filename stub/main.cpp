#include "common.h"

/*  Defines  */

#define IMG_OBJECT_W    8
#define IMG_OBJECT_H    8

/*  Typedefs  */

/*  Macro functions  */

/*  Local Functions  */

/*  Local Variables  */

PROGMEM static const uint8_t imgObject[] = { // 8x8
    0x3C, 0x7E, 0xFF, 0xE7, 0xE7, 0xFF, 0x7E, 0x3C
};

PROGMEM static const uint8_t soundStart[] = {
    72, 12, 74, 12, 76, 12, 77, 12, 79, 36, 0xFF
};

PROGMEM static const uint8_t soundOver[] = {
    55, 13, 54, 16, 53, 19, 52, 22, 51, 25, 50, 28, 49, 31, 48, 34, 0xFF
};

static uint16_t toneFreq;
static char     strBuf[16];

/*---------------------------------------------------------------------------*/

void initMain(void)
{
    for (int8_t i = 0; i < 8; i++) {
        setSprite(i, random(WIDTH - IMG_OBJECT_W), random(HEIGHT - IMG_OBJECT_H), imgObject,
                IMG_OBJECT_W, IMG_OBJECT_H, i % 4);
    }
    setString(2, 6, F("STUB PROGRAM"), WHITE);
    setString(3, 12, F(APP_CODE), WHITE);
    setString(4, 12, F("V" APP_VERSION), WHITE);
    toneFreq = 440;
    counter = 0;
    isInvalid = true;
}

MODE_T updateMain(void)
{
    if (isButtonDown(A_BUTTON)) {
        playScore(soundStart);
        for (int8_t i = 0; i < 8; i++) {
            moveSprite(i, random(WIDTH - IMG_OBJECT_W), random(HEIGHT - IMG_OBJECT_H));
        }
        isInvalid = true;
    }
    if (isButtonPressed(UP_BUTTON | DOWN_BUTTON)) {
        counter += isButtonPressed(DOWN_BUTTON) - isButtonPressed(UP_BUTTON);
        isInvalid = true;
    }
    if (isButtonPressed(LEFT_BUTTON | RIGHT_BUTTON)) {
        toneFreq += isButtonPressed(RIGHT_BUTTON) - isButtonPressed(LEFT_BUTTON);
        playTone(toneFreq, 50);
        sprintf(strBuf, "%dHZ", toneFreq);
        setString(9, 6, strBuf, WHITE);
        isInvalid = true;
    }
    return MODE_MAIN;
}

void drawMain(int16_t y, uint8_t *pBuffer)
{
    memset(pBuffer, bit(counter & 7), WIDTH);
}
