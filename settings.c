#include <ncurses.h>
#include "menu.h"

void show_settings() {
    printw("Opening settings menu...\n");
    refresh();
    getch();
}



