#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <stddef.h>
#include "bet.h"

typedef struct {
    uint32_t balance;
    int32_t current_transaction;
    size_t size;
    size_t capacity;
    Bet *bets;
} Player;

int player_add_bet(Player *player, BetType bet_type, int32_t nums[6], uint32_t amount);
void player_init(Player *player, uint32_t initial_balance);
void player_destroy(Player *player);

#endif