#include "table.h"
#include <stdlib.h>
#include <stdio.h>

int red[36] = {
    1, 0, 1, 0, 1, 0, 1, 0, 
    1, 0, 0, 1, 0, 1, 0, 1, 
    0, 1, 1, 0, 1, 0, 1, 0, 
    1, 0, 1, 0, 0, 1, 0, 1, 
    0, 1, 0, 1
};


size_t random_number() {
    return rand() % 37;
}

static int in_nums(uint32_t x, int32_t nums[6]) {
    size_t i;
    for (i = 0; i < 6; i++) {
        if (nums[i] == -1) return 0;
        if (nums[i] == x) return 1;
    }
    return 0;
}

void spin(Player *player) {
    size_t r = random_number();
    printf("Rolled number %ld\n", r);

    Bet *cur;
    size_t i = 0;
    for (cur = player->bets; cur < player->bets + player->size; cur++) {
        switch (cur->bet_type) {
            case RED:
                if (r != 0 && red[r - 1]) {
                    player->current_transaction += 2 * cur->amount;
                }
                break;
            case BLACK:
                if (r != 0 && !red[r - 1]) {
                    player->current_transaction += 2 * cur->amount;
                }
                break;
            case ODD:
                if (r != 0 && r % 2 != 0) {
                    player->current_transaction += 2 * cur->amount;
                }
                break;
            case EVEN:
                if (r != 0 && r % 2 == 0) {
                    player->current_transaction += 2 * cur->amount;
                }
                break;
            case HIGH:
                if (r > 18) {
                    player->current_transaction += 2 * cur->amount;
                }
                break;
            case LOW:
                if (r != 0 && r < 19) {
                    player->current_transaction += 2 * cur->amount;
                }
                break;
            case LEFT_COLUMN:
                if (r % 3 == 1) {
                    player->current_transaction += 3 * cur->amount;
                }
                break;
            case MIDDLE_COLUMN:
                if (r % 3 == 2) {
                    player->current_transaction += 3 * cur->amount;
                }
                break;
            case RIGHT_COLUMN:
                if (r != 0 && r % 3 == 0) {
                    player->current_transaction += 3 * cur->amount;
                }
                break;
            case LOW_BLOCK:
                if (r != 0 && r < 13) {
                    player->current_transaction += 3 * cur->amount;
                }
                break;
            case MIDDLE_BLOCK:
                if (r > 12 && r < 25) {
                    player->current_transaction += 3 * cur->amount;
                }
                break;
            case HIGH_BLOCK:
                if (r > 24) {
                    player->current_transaction += 3 * cur->amount;
                }
                break;
            case ONE:
                if (in_nums(r, cur->nums)) {
                    player->current_transaction += 36 * cur->amount;
                }
                break;
            case TWO:
                if (in_nums(r, cur->nums)) {
                    player->current_transaction += 18 * cur->amount;
                }
                break;
            case THREE:
                if (in_nums(r, cur->nums)) {
                    player->current_transaction += 12 * cur->amount;
                }
                break;
            case FOUR:
                if (in_nums(r, cur->nums)) {
                    player->current_transaction += 8 * cur->amount;
                }
                break;
            case SIX:
                if (in_nums(r, cur->nums)) {
                    player->current_transaction += 6 * cur->amount;
                }
                break;
            default:
                // Handle unknown bet type
                break;
        }
    }
    
    player->balance += player->current_transaction;
    player->current_transaction = 0;
    clear_bets(player);
}

void clear_bets(Player *player) {
    free(player->bets);
    player->bets = malloc(sizeof(bet) * 16);
    if (!player->bets) {
        perror("error using malloc");
        exit(1);
    }
    player->capacity = 16;
    player->size = 0;
}