#include "player.h"
#include <stdlib.h>
#include <stdio.h>

int player_add_bet(Player *player, BetType bet_type, int32_t nums[6], uint32_t amount) {
    if (player->capacity < player->size + 1) {
        player->capacity *= 2;
        if(!realloc(player->bets, sizeof(Bet) * player->capacity)) {
            perror("Error using realloc");
            return 0;
        }
    }
    player->bets[player->size].bet_type = bet_type;
    player->bets[player->size].amount = amount;
    size_t i;
    for (i = 0; i < 6; i++) {
        player->bets[player->size].nums[i] = nums[i];
    }
    player->size++;
    player->current_transaction -= amount;
    return 1;
}

void player_init(Player *player, uint32_t initial_balance) {
    player->balance = initial_balance;
    player->current_transaction = 0;
    player->size = 0;
    player->capacity = 16;
    player->bets = malloc(sizeof(Bet) * player->capacity);
    if (!player->bets) {
        perror("errer using malloc");
        exit(1);
    }
}

void player_destroy(Player *player) {
    free(player->bets);
    player->bets = NULL;
}