#include "common.h"
#include "data.h"

/*  Defines  */

#define BOARD_SIZE   4

enum STATE_T : uint8_t {
    STATE_IDLE = 0,
    STATE_MOVING,
    STATE_OVER,
};

/*  Typedefs  */

typedef struct {
    uint8_t     value : 5;
    uint8_t     merged : 1;
    uint8_t     move : 2;
} TILE_T;

/*  Local Functions  */

static void initBoard(void);
static int8_t getTileValue(int8_t x, int8_t y);
static void addRandomTile(void);
static bool moveTiles(int8_t vx, int8_t vy);
static void updateTiles(void);
static bool isGameOver(void);
static void forwardTime(void);
static void updateSprites(void);
static void updateScoreSting(void);
static void updateTimeString(void);
static char *num2str(char *p, uint32_t value);

/*  Local Variables  */

static STATE_T state;
static TILE_T board[BOARD_SIZE][BOARD_SIZE];
static uint32_t score;
static uint8_t empty, timeMinutes, timeSeconds, timeFrames;
static int8_t moveVx, moveVy, addedIdx;
static char scoreString[7], timeString[7];

/*---------------------------------------------------------------------------*/
/*                               Main Functions                              */
/*---------------------------------------------------------------------------*/

void initGame(void)
{
    initSprites();
    initStrings();
    setString(0, 99, F("SCORE"), WHITE);
    setString(3, 105, F("TIME"), WHITE);
    score = 0;
    scoreString[6] = '\0';
    timeMinutes = timeSeconds = timeFrames = 0;
    timeString[6] = '\0';
    updateTimeString();
    setString(1, 93, scoreString, WHITE);
    setString(4, 93, timeString, WHITE);

    initBoard();
    addRandomTile();
    addRandomTile();
    updateTiles();
    counter = 0;
    addedIdx = -1;
    state = STATE_IDLE;
    playScore(soundStart);
}

MODE_T updateGame(void)
{
    MODE_T ret = MODE_GAME;
    if (counter < FPS) counter++;
    if (state == STATE_IDLE) {
        forwardTime();
        moveVx = isButtonDown(RIGHT_BUTTON) - isButtonDown(LEFT_BUTTON);
        moveVy = isButtonDown(DOWN_BUTTON) - isButtonDown(UP_BUTTON);
        if (moveVx != 0 && moveVy == 0 || moveVx == 0 && moveVy != 0) {
            if (moveTiles(moveVx, moveVy)) {
                counter = 1;
                state = STATE_MOVING;
            }
        }
    } else if (state == STATE_MOVING) {
        forwardTime();
        if (counter == 8) {
            addRandomTile();
            updateTiles();
            counter = 0;
            if (isGameOver()) {
                setString(8, 96, F("GAME"), WHITE);
                setString(9, 105, F("OVER"), WHITE);
                playScore(soundOver);
                state = STATE_OVER;
            } else {
                state = STATE_IDLE;
            }
        }
    } else if (state == STATE_OVER) {
        if (isButtonDown(A_BUTTON)) ret = MODE_TITLE;
    }
    updateSprites();
    return ret;
}

void drawGame(int16_t y, uint8_t *pBuffer)
{
    const uint8_t *p = &imgTile[0][(y & 0x08) ? IMG_TILE_W - 1 : 0];
    for (uint8_t i = 0; i < BOARD_SIZE; i++) {
        memcpy_P(pBuffer + i * IMG_TILE_W, p, IMG_TILE_W - 1);
        pBuffer[(i + 1) * IMG_TILE_W - 1] = 0x00;
    }
    memset(pBuffer + IMG_TILE_W * BOARD_SIZE, 0x00, WIDTH - IMG_TILE_W * BOARD_SIZE);
}

/*---------------------------------------------------------------------------*/
/*                             Control Functions                             */
/*---------------------------------------------------------------------------*/

static void initBoard(void)
{
    memset(board, 0, sizeof(board));
    empty = BOARD_SIZE * BOARD_SIZE;
}

static int8_t getTileValue(int8_t x, int8_t y)
{
    return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) ? board[y][x].value : -1;
}

static void addRandomTile(void)
{
    int8_t position = random() % empty;
    for (int8_t y = 0; y < BOARD_SIZE; y++) {
        for (int8_t x = 0; x < BOARD_SIZE; x++) {
            TILE_T *p = &board[y][x];
            if (p->value == 0 && position-- == 0) {
                p->value = (random() % 10 == 0) ? 2 : 1;
                empty--;
                addedIdx = y * BOARD_SIZE + x;
                return;
            }
        }
    }
}

static bool moveTiles(int8_t vx, int8_t vy)
{
    bool ret = false;
    for (int8_t i = 0; i < BOARD_SIZE; i++) {
        for (int8_t j = 0; j < BOARD_SIZE; j++) {
            int8_t x = (vx > 0) ? BOARD_SIZE - 1 - j : j;
            int8_t y = (vy > 0) ? BOARD_SIZE - 1 - i : i;
            TILE_T *p = &board[y][x];
            p->move = 0;
            if (p->value > 0) {
                int8_t value = p->value, nextValue;
                p->value = 0;
                p->merged = false;
                do {
                    p->move++;
                    x += vx;
                    y += vy;
                    nextValue = getTileValue(x, y);
                } while (nextValue == 0);
                if (nextValue == value && !board[y][x].merged) {
                    board[y][x].merged = true;
                    empty++;
                } else {
                    p->move--;
                    board[y - vy][x - vx].value = value;
                }
                if (p->move > 0) ret = true;
            }
        }
    }
    return ret;
}

static void updateTiles(void)
{
    uint8_t soundValue = 0;
    for (int8_t y = 0, idx = 0; y < BOARD_SIZE; y++) {
        for (int8_t x = 0; x < BOARD_SIZE; x++, idx++) {
            TILE_T *p = &board[y][x];
            if (p->merged) {
                p->value++;
                score += 1 << p->value;
                if (soundValue < p->value) soundValue = p->value;
            }
            if (p->value > 0) {
                setSprite(idx, x * IMG_TILE_W, y * IMG_TILE_H, imgTile[p->value],
                        IMG_TILE_W - 1, IMG_TILE_H - 1, SPECIAL);
            } else {
                clearSprite(idx);
            }
        }
    }
    if (score > 999999) score = 999999;
    updateScoreSting();
    playScore((const uint8_t *)pgm_read_word(&soundMergeTable[soundValue]));
    isInvalid = true;
}

static bool isGameOver(void)
{
    if (empty > 0) return false;
    for (int8_t y = 0; y < BOARD_SIZE; y++) {
        for (int8_t x = 0; x < BOARD_SIZE; x++) {
            int8_t value = getTileValue(x, y);
            if (value == 0) return false;
            if (getTileValue(x - 1, y) == value || getTileValue(x + 1, y) == value ||
                getTileValue(x, y - 1) == value || getTileValue(x, y + 1) == value) return false;
        }
    }
    return true;
}

static void forwardTime(void)
{
    if (++timeFrames == FPS) {
        timeFrames = 0;
        if (++timeSeconds == 60) {
            timeSeconds = 0;
            timeMinutes++;
        }
        updateTimeString();
    }
}

static void updateSprites(void)
{
    if (state == STATE_IDLE) {
        if (counter < 18) {
            for (int8_t y = 0, idx = 0; y < BOARD_SIZE; y++) {
                for (int8_t x = 0; x < BOARD_SIZE; x++, idx++) {
                    TILE_T *p = &board[y][x];
                    if (p->merged && p->value >= counter) {
                        int8_t g = p->value - counter;
                        int8_t gx = random(g * 2 + 1) - g;
                        int8_t gy = g - abs(gx);
                        if (random(2)) gy = -gy;
                        moveSprite(idx, x * IMG_TILE_W + gx, y * IMG_TILE_H + gy);
                        isInvalid = true;
                    }
                }
            }
            if (addedIdx >= 0 && counter < 8) {
                moveSprite(addedIdx, addedIdx % BOARD_SIZE * IMG_TILE_W,
                    (counter & 1) ? addedIdx / BOARD_SIZE * IMG_TILE_H : HEIGHT);
                isInvalid = true;
            }
        }
    } else if (state == STATE_MOVING) {
        if (counter <= 8) {
            for (int8_t y = 0, idx = 0; y < BOARD_SIZE; y++) {
                for (int8_t x = 0; x < BOARD_SIZE; x++, idx++) {
                    TILE_T *p = &board[y][x];
                    moveSprite(idx, x * IMG_TILE_W + p->move * moveVx * counter * 3,
                            y * IMG_TILE_H + p->move * moveVy * counter * 2);
                }
            }
            isInvalid = true;
        }
    }
}

static void updateScoreSting(void)
{
    char *p = num2str(&scoreString[5], score);
    while (p >= scoreString) {
        *p-- = ' ';
    }
    isInvalid = true;
}

static void updateTimeString(void)
{
    num2str(&timeString[5], timeSeconds + 100);
    char *p = num2str(&timeString[2], timeMinutes);
    while (p >= timeString) {
        *p-- = ' ';
    }
    timeString[3] = ':';
    isInvalid = true;
}

static char *num2str(char *p, uint32_t value)
{
    do {
        *p-- = (value % 10) + '0';
        value /= 10UL;
    } while (value > 0);
    return p;
}
