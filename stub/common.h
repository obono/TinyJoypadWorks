#pragma once

#include "core.h"

/*  Defines  */

#define FPS             30
#define APP_CODE        "OBN-T00"
#define APP_VERSION     "0.1"

enum MODE_T : uint8_t {
    MODE_MAIN = 0,
};

/*  Global Functions  */

void    initMain(void);
MODE_T  updateMain(void);
void    drawMain(int16_t y, uint8_t *pBuffer);

/*  Macro Functions  */

/*  Global Variables  */
