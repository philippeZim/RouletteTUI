#ifndef TUI_H
#define TUI_H

#include <stdint.h>
#include "table.h"

void reset(uint32_t x, Player *player);
void print_help(void);
int get_input(Player *player);
int command_parser(char *input, Player *player);
int bet_parser(char *input, Player *player);
int reset_parser(char *input, Player *player);

#endif