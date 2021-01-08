#pragma once

#include "core.h"

/*  Defines  */

#define FPS             30
#define APP_CODE        "OBN-T02"
#define APP_VERSION     "0.2"
#define RECORD_TOKEN    0x024E424FUL // "OBN\x02"

enum MODE_T : uint8_t {
    MODE_LOGO = 0,
    MODE_TITLE,
    MODE_GAME,
};

enum : uint8_t {
    LEVEL_EASY = 0,
    LEVEL_MEDIUM,
    LEVEL_HARD,
    LEVEL_EXPERT,
    LEVEL_MAX
};

/*  Global Functions  */

void    initLogo(void);
MODE_T  updateLogo(void);

void    initTitle(void);
MODE_T  updateTitle(void);

void    initGame(void);
MODE_T  updateGame(void);
void    drawGame(int16_t y, uint8_t *pBuffer);
void    playSoundTick(void);
void    playSoundClick(void);

/*  Global Variables  */

extern uint8_t  level;
