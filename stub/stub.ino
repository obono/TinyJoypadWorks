#ifdef DISABLEMILLIS
#include <util/delay.h>
#endif
#include "common.h"

/*  Typedefs  */

typedef struct {
    void    (*initFunc)(void);
    MODE_T  (*updateFunc)(void);
    void    (*drawFunc)(int16_t, uint8_t *);
} MODULE_FUNCS;

/*  Macro functions  */

#define callInitFunc(idx)       ((void (*)(void)) pgm_read_word(&moduleTable[idx].initFunc))()
#define callUpdateFunc(idx)     ((MODE_T (*)(void)) pgm_read_word(&moduleTable[idx].updateFunc))()
#define pointerDrawFunc(idx)    ((void (*)(int16_t, uint8_t *)) pgm_read_word(&moduleTable[idx].drawFunc))

/*  Local Variables  */

PROGMEM static const MODULE_FUNCS moduleTable[] = {
    { initMain,  updateMain,  drawMain  },
};

static MODE_T   mode = MODE_MAIN;
#ifndef DISABLEMILLIS
static uint32_t targetTime;
#endif

/*---------------------------------------------------------------------------*/

void setup(void)
{
    initCore();
    callInitFunc(mode);
#ifndef DISABLEMILLIS
    targetTime = millis();
#endif
}

void loop(void)
{
    updateButtonState();
    MODE_T nextMode = callUpdateFunc(mode);
    refreshScreen(pointerDrawFunc(mode));
    if (mode != nextMode) {
        mode = nextMode;
        callInitFunc(mode);
    }
#ifdef DISABLEMILLIS
    _delay_ms(1000.0 / (double)FPS);
#else
    targetTime += 1000 / FPS;
    uint32_t delayTime = targetTime - millis();
    if (!bitRead(delayTime, 31)) delay(delayTime);
#endif
}
