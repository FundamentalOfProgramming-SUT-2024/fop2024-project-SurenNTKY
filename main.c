#include <stdio.h>
#include <ncurses.h>
#include "user.h"

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int win_height = 10;
    int win_width = 50;
    int start_y = (max_y - win_height) / 2;
    int start_x = (max_x - win_width) / 2;

    WINDOW *win = newwin(win_height, win_width, start_y, start_x);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "1. Login");
    mvwprintw(win, 2, 1, "2. Register");
    mvwprintw(win, 3, 1, "3. Guest");
    mvwprintw(win, 8, 1, "Press the corresponding number to choose.");
    wrefresh(win);

    int ch;
    while ((ch = getch()) != '1' && ch != '2' && ch != '3') { }

    delwin(win);

    switch (ch) {
        case '1':
            login();
            break;
        case '2':
            register_user();
            break;
        case '3':
            guest();
            break;
        default:
            break;
    }

    endwin();
    return 0;
}



