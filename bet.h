#ifndef BET_H
#define BET_H

#include <stdint.h>

typedef enum {
    RED,
    BLACK,
    ODD,
    EVEN,
    HIGH,
    LOW,
    LEFT_COLUMN,
    MIDDLE_COLUMN,
    RIGHT_COLUMN,
    LOW_BLOCK,
    MIDDLE_BLOCK,
    HIGH_BLOCK,
    ONE,
    TWO,
    THREE,
    FOUR,
    SIX
} BetType;

typedef struct {
    BetType bet_type;
    int32_t nums[6];
    uint32_t amount;
} Bet;

#endif