#include <ncurses.h>
#include "game.h"

void show_scoreboard() {
    printw("Displaying the scoreboard...\n");
    refresh();
    getch();
}



