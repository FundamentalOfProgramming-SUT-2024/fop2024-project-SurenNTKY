#include <stdio.h>
#include <ncurses.h>
#include "user.h"

void guest() {
    WINDOW *win = newwin(5, 40, 5, 5);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Welcome, Guest! Press ESC to quit.");
    wrefresh(win);

    int ch;
    while ((ch = getch()) != 27) { }

    delwin(win);
}



