#include <ncurses.h>
#include "game.h"

void continue_game() {
    printw("Continuing the previous game...\n");
    refresh();
    getch();
}



