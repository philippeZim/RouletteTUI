#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "bet.h"


void bet(BetType bet_type, uint32_t *nums, size_t n, uint32_t amount, Player *player);
uint32_t *get_number_for_bet_range(uint32_t from, uint32_t to);
int one_bet(uint32_t a, uint32_t amount, Player *player);
int range_bet(uint32_t a, uint32_t b, uint32_t amount, Player *player);
int four_bet(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t amount, Player *player);
int binary_bet(BetType bet_type, uint32_t amount, Player *player);
int column_bet(BetType bet_type, uint32_t amount, Player *player);
int block_bet(BetType bet_type, uint32_t amount, Player *player);
void spin(Player *player);
size_t random_number(void);
void clear_bets(Player *player);

extern int red[36];

#endif