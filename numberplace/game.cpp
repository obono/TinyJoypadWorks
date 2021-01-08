#include "common.h"
#include "data.h"

/*  Defines  */

#define BOARD_SIZE  9
#define CELL_SIZE   7
#define UNIT_SIZE   (CELL_SIZE * 3)

#define DIGITS      (BOARD_SIZE + 1)
#define LONG_PRESS  10

enum : uint8_t {
    SPR_ID_STATE = 0,
    SPR_ID_TOOL,
    SPR_ID_NUMBER,
    SPR_ID_CURSOR,
    SPR_ID_LOCKED
};

/*  Typedefs  */

typedef struct {
    uint8_t     number : 4;
    uint8_t     locked : 1;
} CELL_T;

/*  Macro functions  */

#define getUnitIndex(x, y)  ((y) / 3 * 3 + (x) / 3)

/*  Local Functions  */

static void     initPuzzle(void);
static void     placeNumber(uint8_t x, uint8_t y, uint8_t n);
static void     removeNumber(uint8_t x, uint8_t y);
static void     updateState(uint8_t x, uint8_t y, uint8_t n, bool isPlace);
static int32_t  powDigits(uint8_t n);

static void     setStateSprite(void);
static void     setToolSprite(void);
static void     setCursorSprite(void);
static void     setSelectingSprite(void);

/*  Global Variables  */

/*  Local Variables  */

static CELL_T   board[BOARD_SIZE][BOARD_SIZE];
static int32_t  boardState[3][BOARD_SIZE], boardFailure;
static uint8_t  selectedNumber, cursorX, cursorY, placedCount;
static bool     isSelecting;

/*---------------------------------------------------------------------------*/
/*                               Main Functions                              */
/*---------------------------------------------------------------------------*/

void initGame(void)
{
    initPuzzle();
    selectedNumber = 1;
    cursorX = cursorY = 4;
    isSelecting = false;
    counter = LONG_PRESS;

    initSprites();
    setToolSprite();
    setCursorSprite();

    playScore(soundStart);
    isInvalid = true;
}

MODE_T updateGame(void)
{
    MODE_T ret = MODE_GAME;
    int8_t vx = isButtonDown(RIGHT_BUTTON) - isButtonDown(LEFT_BUTTON);
    int8_t vy = isButtonDown(DOWN_BUTTON) - isButtonDown(UP_BUTTON);

    if (isSelecting) {
        /*  Select tool  */
        if (vx) {
            selectedNumber = circulate(selectedNumber, vx, DIGITS);
            setToolSprite();
            playTone(440, 50);
            isInvalid = true;
        }
        /*  Exit selecting mode  */
        if (isButtonDown(A_BUTTON)) {
            isSelecting = false;
            playTone(380, 100);
            isInvalid = true;
        }
    } else {
        /*  Move cursor  */
        if (vx || vy) {
            cursorX = circulate(cursorX, vx, BOARD_SIZE);
            cursorY = circulate(cursorY, vy, BOARD_SIZE);
            playTone(440, 50);
            isInvalid = true;
        }
        if (isButtonPressed(A_BUTTON)) {
            /*  Enter selecting mode  */
            if (++counter == LONG_PRESS) {
                isSelecting = true;
                setSelectingSprite();
                playTone(500, 100);
                isInvalid = true;
            }
        } else {
            /*  Place or remove number  */
            if (counter > 0 && counter < LONG_PRESS) {
                if (board[cursorY][cursorX].locked) {
                    playTone(1320, 50);
                } else {
                    uint8_t n = board[cursorY][cursorX].number;
                    if (selectedNumber > 0 && n != selectedNumber) {
                        placeNumber(cursorX, cursorY, selectedNumber);
                        playTone(660, 200);
                    } else if (selectedNumber == 0 && n > 0 ||
                            selectedNumber > 0 && n == selectedNumber) {
                        removeNumber(cursorX, cursorY);
                        playTone(380, 200);
                    }
                    const uint8_t *pImg = NULL;
                    if (boardFailure) {
                        pImg = imgState[1];
                    } else if (placedCount == BOARD_SIZE * BOARD_SIZE) {
                        pImg = imgState[0];
                    }
                    setSprite(SPR_ID_STATE, 10, 24, pImg, IMG_STATE_W, IMG_STATE_H, DIRECT);
                    isInvalid = true;
                }
            }
            counter = 0;
        }
    }
    if (!isSelecting) setCursorSprite();

    //if (isButtonDown(A_BUTTON)) {
    //    initGame();
    //} else if (--counter == 0) {
    //    ret = MODE_TITLE;
    //}

    return ret;
}

void drawGame(int16_t y, uint8_t *pBuffer)
{
    clearScreenBuffer();

    /*  Digits  */
    uint8_t by = y >> 3;
    for (uint8_t bx = 0; bx < BOARD_SIZE; bx++) {
        uint8_t n1 = board[by][bx].number;
        uint8_t n2 = board[by + 1][bx].number;
        uint8_t *p = pBuffer + 34 + bx * CELL_SIZE;
        const uint8_t *pImg1 = imgDigit[n1];
        const uint8_t *pImg2 = imgDigit[n2];
        for (uint8_t w = 0; w < IMG_DIGIT_W; w++) {
            *p++ = pgm_read_byte(pImg1++) >> by | pgm_read_byte(pImg2++) << (CELL_SIZE - by);
        }
    }

    /*  Grid  */
    uint8_t dy = (y + CELL_SIZE - 1) / CELL_SIZE * CELL_SIZE;
    for (uint8_t ptn = 1 << (dy - y); ptn; ptn <<= CELL_SIZE, dy += CELL_SIZE) {
        uint8_t vx = (dy % UNIT_SIZE == 0) ? CELL_SIZE : UNIT_SIZE;
        for (uint8_t x = 32; x < 96; x += vx) {
            *(pBuffer + x) |= ptn;
        }
    }
}

/*---------------------------------------------------------------------------*/
/*                             Control Functions                             */
/*---------------------------------------------------------------------------*/

static void initPuzzle(void)
{
    memset(board, 0, sizeof(board));
    memset(boardState, 0, sizeof(boardState));
    placedCount = 0;
    boardFailure = 0;
    for (uint8_t y = 0; y < BOARD_SIZE; y++) {
        int32_t rowData = (int32_t)pgm_read_dword(&puzzleData[0][y]);
        for (uint8_t x = 0; x < BOARD_SIZE; x++) {
            uint8_t n = rowData % DIGITS;
            if (n) {
                placeNumber(x, y, n);
                board[y][x].locked = true;
            }
            rowData /= (int32_t)DIGITS;
        }
    }
}

static void placeNumber(uint8_t x, uint8_t y, uint8_t n)
{
    if (board[y][x].number > 0) removeNumber(x, y);
    board[y][x].number = n;
    placedCount++;
    updateState(x, y, n, true);
}

static void removeNumber(uint8_t x, uint8_t y)
{
    uint8_t n = board[y][x].number;
    if (n == 0) return;
    board[y][x].number = 0;
    placedCount--;
    updateState(x, y, n, false);
}

static void updateState(uint8_t x, uint8_t y, uint8_t n, bool isPlace)
{
    int32_t q = powDigits(n);
    for (uint8_t i = 0; i < 3; i++) {
        uint8_t idx = (i == 2) ? getUnitIndex(x, y) : ((i == 1) ? y : x);
        boardState[i][idx] += (isPlace) ? q : -q;
        uint8_t a = boardState[i][idx] / q % DIGITS;
        uint8_t b = i * DIGITS + n;
        if (isPlace  && a == 2) bitSet(boardFailure, b);
        if (!isPlace && a == 1) bitClear(boardFailure, b);
    }
}

static int32_t powDigits(uint8_t n)
{
    int32_t q = 1;
    while (--n > 0) {
        q *= (int32_t)DIGITS;
    }
    return q;
}

/*---------------------------------------------------------------------------*/

static void setToolSprite(void)
{
    setSprite(SPR_ID_TOOL, 106, 24, imgTool[!selectedNumber], IMG_TOOL_W, IMG_TOOL_H, DIRECT);
    setSprite(SPR_ID_NUMBER, 110, 25, imgDigit[selectedNumber], IMG_DIGIT_W, IMG_DIGIT_H, WHITE);
}

static void setCursorSprite(void)
{
    setSprite(SPR_ID_CURSOR, cursorX * CELL_SIZE + 32, cursorY * CELL_SIZE, imgCursor,
            IMG_CURSOR_W, IMG_CURSOR_H, WHITE);
    setSprite(SPR_ID_LOCKED, 108, 40, (board[cursorY][cursorX].locked) ? imgLocked : NULL,
            IMG_LOCKED_W, IMG_LOCKED_H, DIRECT);
}

static void setSelectingSprite(void)
{
    setSprite(SPR_ID_CURSOR, 102, 24, imgSelecting, IMG_SELECTING_W, IMG_SELECTING_H, WHITE);
}
