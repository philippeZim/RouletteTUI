#include "tui.h"
#include <stdio.h>
#include <string.h>

void reset(uint32_t x, Player *player) {
    player->balance = x;
    player->current_transaction = 0;
}

void print_help(void) {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                 ROULETTE GAME - COMMAND HELP                 ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("ACCOUNT MANAGEMENT:\n");
    printf("  /reset {amount}     - Reset your balance to the specified amount\n");
    printf("  /balance            - Display your current balance\n\n");
    
    printf("BETTING COMMANDS:\n");
    printf("  /bet {number} {amount}                        - Bet on a single number (pays 36x)\n");
    printf("  /bet {n1} {n2} {amount}                       - Bet on 2 numbers (pays 18x)\n");
    printf("  /bet {n1} {n2} {n3} {amount}                  - Bet on 3 numbers (pays 12x)\n");
    printf("  /bet {n1} {n2} {n3} {n4} {amount}             - Bet on 4 numbers (pays 8x)\n");
    printf("  /bet {n1} {n2} {n3} {n4} {n5} {n6} {amount}   - Bet on 6 numbers (pays 6x)\n\n");
    
    printf("OUTSIDE BETS (2x payout):\n");
    printf("  /bet RED {amount}                             - Bet on red numbers\n");
    printf("  /bet BLACK {amount}                           - Bet on black numbers\n");
    printf("  /bet EVEN {amount}                            - Bet on even numbers\n");
    printf("  /bet ODD {amount}                             - Bet on odd numbers\n");
    printf("  /bet HIGH {amount}                            - Bet on numbers 19-36\n");
    printf("  /bet LOW {amount}                             - Bet on numbers 1-18\n\n");
    
    printf("COLUMN BETS (3x payout):\n");
    printf("  /bet LEFT_COLUMN {amount}                     - Bet on left column (1,4,7,...)\n");
    printf("  /bet MIDDLE_COLUMN {amount}                   - Bet on middle column (2,5,8,...)\n");
    printf("  /bet RIGHT_COLUMN {amount}                    - Bet on right column (3,6,9,...)\n\n");
    
    printf("DOZEN BETS (3x payout):\n");
    printf("  /bet LOW_BLOCK {amount}                       - Bet on 1st dozen (1-12)\n");
    printf("  /bet MIDDLE_BLOCK {amount}                    - Bet on 2nd dozen (13-24)\n");
    printf("  /bet HIGH_BLOCK {amount}                      - Bet on 3rd dozen (25-36)\n\n");
    
    printf("GAME ACTION:\n");
    printf("  /spin                                         - Spin the roulette wheel\n\n");
    
    printf("EXAMPLES:\n");
    printf("  /bet 17 10                                    - Bet 10 on number 17\n");
    printf("  /bet RED 20                                   - Bet 20 on red\n");
    printf("  /reset 1000                                   - Reset balance to 1000\n\n");
}

int get_input(Player *player) {
    char input[128];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        int res = command_parser(input, player);
        if (res) {
            return 1;
        }
    }
    return 0;
}

int command_parser(char *input, Player *player) {
    if (strncmp(input, "/bet ", 5) == 0) {
        return bet_parser(input, player);
    }
    if (strncmp(input, "/spin", 5) == 0) {
        spin(player);
        return 1;
    }
    if (strncmp(input, "/balance", 8) == 0) {
        printf("%d\n", player->balance);
        return 1;
    }
    if (strncmp(input, "/reset ", 7) == 0) {
        return reset_parser(input, player);
    }
    return 0;
}
int bet_parser(char *input, Player *player) {
    char keyword[20];
    uint32_t amount;
    uint32_t n1, n2, n3, n4, n5, n6;
    if (sscanf(input, "/bet %u %u %u %u %u %u %u", &n1, &n2, &n3, &n4, &n5, &n6, &amount) == 7) {
        return player_add_bet(player, SIX, (int32_t[6]){n1, n2, n3, n4, n5, n6}, amount);
    }
    if (sscanf(input, "/bet %u %u %u %u %u", &n1, &n2, &n3, &n4, &amount) == 5) {
        return player_add_bet(player, FOUR, (int32_t[6]){n1, n2, n3, n4, -1, -1}, amount);
    }
    if (sscanf(input, "/bet %u %u %u %u", &n1, &n2, &n3, &amount) == 4) {
        return player_add_bet(player, THREE, (int32_t[6]){n1, n2, n3, -1, -1, -1}, amount);
    }
    if (sscanf(input, "/bet %u %u %u", &n1, &n2, &amount) == 3) {
        return player_add_bet(player, TWO, (int32_t[6]){n1, n2, n3, -1, -1, -1}, amount);
    }
    if (sscanf(input, "/bet %u %u", &n1, &amount) == 2) {
        return player_add_bet(player, ONE, (int32_t[6]){n1, n2, -1, -1, -1, -1}, amount);
    }
    if (sscanf(input, "/bet %19s %u", keyword, &amount) == 2) {
        if (strcmp(keyword, "RED") == 0) {
            return player_add_bet(player, RED, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
        if (strcmp(keyword, "BLACK") == 0) {
            return player_add_bet(player, BLACK, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
        if (strcmp(keyword, "EVEN") == 0) {
            return player_add_bet(player, EVEN, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
        if (strcmp(keyword, "ODD") == 0) {
            return player_add_bet(player, ODD, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
        if (strcmp(keyword, "HIGH") == 0) {
            return player_add_bet(player, HIGH, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
        if (strcmp(keyword, "LOW") == 0) {
            return player_add_bet(player, LOW, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
        if (strcmp(keyword, "LEFT_COLUMN") == 0) {
            return player_add_bet(player, LEFT_COLUMN, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
        if (strcmp(keyword, "MIDDLE_COLUMN") == 0) {
            return player_add_bet(player, MIDDLE_COLUMN, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
        if (strcmp(keyword, "RIGHT_COLUMN") == 0) {
            return player_add_bet(player, RIGHT_COLUMN, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
        if (strcmp(keyword, "LOW_BLOCK") == 0) {
            return player_add_bet(player, LOW_BLOCK, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
        if (strcmp(keyword, "MIDDLE_BLOCK") == 0) {
            return player_add_bet(player, MIDDLE_BLOCK, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
        if (strcmp(keyword, "HIGH_BLOCK") == 0) {
            return player_add_bet(player, HIGH_BLOCK, (int32_t[6]){-1, -1, -1, -1, -1, -1}, amount);
        }
    }
    
    printf("Invalid bet command format.\n");
    return 0;
}

int reset_parser(char *input, Player *player) {
    uint32_t amount;
    if (sscanf(input, "/reset %u", &amount) == 1) {
        reset(amount, player);
        return 1;
    }
    return 0;
}
