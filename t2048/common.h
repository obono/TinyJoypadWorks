#pragma once

#include "core.h"

/*  Defines  */

#define FPS             30
#define APP_CODE        "OBN-T03"
#define APP_VERSION     "0.2"
#define RECORD_TOKEN    0x034E424FUL // "OBN\x03"

enum MODE_T : uint8_t {
    MODE_LOGO = 0,
    MODE_TITLE,
    MODE_GAME,
};

/*  Global Functions  */

void    initLogo(void);
MODE_T  updateLogo(void);

void    initTitle(void);
MODE_T  updateTitle(void);

void    initGame(void);
MODE_T  updateGame(void);
void    drawGame(int16_t y, uint8_t *pBuffer);
