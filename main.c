#include "tui.h"
#include "table.h"
#include "player.h"
#include <stdio.h>
#include <time.h>

int main() {
    srand(time(NULL));
    uint32_t balance;
    int32_t current_transaction;
    size_t size;
    size_t capacity;
    Bet *bets;
    Player p1;
    player_init(&p1, 100);
    print_help();
        
    while (get_input(&p1)) {}
    player_destroy(&p1);
    printf("\nEnd of input detected. Goodbye!\n");
    return 0;
}