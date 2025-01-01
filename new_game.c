#include <ncurses.h>
#include "game.h"

void new_game() {
    printw("Starting a new game...\n");
    refresh();
    getch();
}



