#include <ncurses.h>
#include "menu.h"

void show_scoreboard()
{
    printw("Displaying the scoreboard...\n");
    refresh();
    getch();
}
