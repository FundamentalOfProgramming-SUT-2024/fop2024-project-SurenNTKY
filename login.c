#include <stdio.h>
#include <ncurses.h>
#include "user.h"

void login() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MIN_LENGTH * 2];

    WINDOW *win = newwin(10, 50, 1, 1);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Enter Username: ");
    mvwprintw(win, 2, 1, "Enter Password: ");
    wrefresh(win);
    echo();
    mvwgetnstr(win, 1, 17, username, USERNAME_MAX_LENGTH);
    mvwgetnstr(win, 2, 17, password, PASSWORD_MIN_LENGTH * 2);

    if (check_username(username) && check_password(password)) {
        mvwprintw(win, 4, 1, "Login successful! Press ESC to quit.");
    } else {
        mvwprintw(win, 4, 1, "Invalid credentials! Press ESC to quit.");
    }
    noecho();

    wrefresh(win);
    int ch;
    while ((ch = getch()) != 27) { }

    delwin(win);
}



