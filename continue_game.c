#include <ncurses.h>
#include "menu.h"

void continue_game() {
    printw("Continuing the previous game...\n");
    refresh();
    getch();
}



