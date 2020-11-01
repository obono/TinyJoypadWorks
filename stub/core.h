#pragma once

#include <Arduino.h>

/*  Defines  */

#define ENABLE_SOUND

#define WIDTH           128
#define HEIGHT          64
#define PAGES           8

#define LEFT_BUTTON     bit(0)
#define RIGHT_BUTTON    bit(1)
#define UP_BUTTON       bit(2)
#define DOWN_BUTTON     bit(3)
#define A_BUTTON        bit(4)

#define BLACK           0
#define WHITE           1
#define INVERT          2
#define DIRECT          3

/*  Global Functions  */

void    initCore(void);
void    refreshScreen(void (*func)(int16_t, uint8_t *));
void    clearScreenBuffer(void);

void    updateButtonState(void);
bool    isButtonPressed(uint8_t b);
bool    isButtonDown(uint8_t b);
bool    isButtonUp(uint8_t b);

void    initSprites(void);
void    setSprite(uint8_t idx, int8_t x, int8_t y, const uint8_t *pBitmap, uint8_t w, uint8_t h, uint8_t color);
void    moveSprite(uint8_t idx, int8_t x, int8_t y);
void    clearSprite(uint8_t idx);
void    drawSprites(int16_t y);

void    initStrings(void);
void    setString(uint8_t idx, int8_t x, const __FlashStringHelper *pFlashString, uint8_t color);
void    setString(uint8_t idx, int8_t x, char *pString, uint8_t color);
void    clearString(uint8_t idx);
void    drawStrings(int16_t y);

#ifdef ENABLE_SOUND
void    playTone(uint16_t frequency, uint16_t duration);
void    playScore(const uint8_t *pScore);
#endif

/*  Macro Functions  */

#define circulate(n, v, m)  (((n) + (v) + (m)) % (m))

/*  Global Variables  */

extern uint8_t  counter;
extern bool     isInvalid;
