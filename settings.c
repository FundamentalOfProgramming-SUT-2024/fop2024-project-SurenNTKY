#include <ncurses.h>
#include "game.h"

void show_settings() {
    printw("Opening settings menu...\n");
    refresh();
    getch();
}



