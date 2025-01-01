#include <ncurses.h>
#include "game.h"

void show_profile() {
    printw("Displaying user profile...\n");
    refresh();
    getch();
}



