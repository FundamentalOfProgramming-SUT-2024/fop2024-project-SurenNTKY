#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

void show_error_login() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int win_height = 8, win_width = 50;
    int start_y = (max_y - win_height) / 2;
    int start_x = (max_x - win_width) / 2;

    WINDOW *win = newwin(win_height, win_width, start_y, start_x);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "Invalid credentials!");
    mvwprintw(win, 3, 2, "[Click here to Retry]");
    mvwprintw(win, 4, 2, "[Click here to Exit]");
    wrefresh(win);

    MEVENT event;
    mousemask(ALL_MOUSE_EVENTS, NULL);

    int ch;
    while ((ch = getch()) != 27) {
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_CLICKED) {
                    if (event.y == start_y + 3 && event.x >= start_x + 2 && event.x <= start_x + 20) {
                        delwin(win);
                        login();
                        return;
                    } else if (event.y == start_y + 4 && event.x >= start_x + 2 && event.x <= start_x + 20) {
                        delwin(win);
                        endwin();
                        printf("Exiting the game...\n");
                        exit(0);
                    }
                }
            }
        }
    }

    delwin(win);
}

void login() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MIN_LENGTH * 2];
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int win_height = 12, win_width = 50;
    int start_y = (max_y - win_height) / 2;
    int start_x = (max_x - win_width) / 2;

    WINDOW *win = newwin(win_height, win_width, start_y, start_x);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "Enter Username: ");
    mvwprintw(win, 2, 2, "Enter Password: ");
    mvwprintw(win, 6, 2, "[Click here to Sign In]");
    wrefresh(win);

    mousemask(0, NULL);

    echo();
    mvwgetnstr(win, 1, 18, username, USERNAME_MAX_LENGTH);
    mvwgetnstr(win, 2, 18, password, PASSWORD_MIN_LENGTH * 2);

    mousemask(ALL_MOUSE_EVENTS, NULL);

    int ch;
    while ((ch = getch()) != 27) {
        if (ch == KEY_MOUSE) {
            MEVENT event;
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_CLICKED) {
                    if (event.y == start_y + 6 && event.x >= start_x + 2 && event.x <= start_x + 20) {
                        if (check_username(username) && check_password(password)) {
                            mvwprintw(win, 7, 2, "Login successful! Redirecting...");
                            wrefresh(win);
                            napms(1000);
                            delwin(win);
                            return;
                        } else {
                            delwin(win);
                            show_error_login();
                            return;
                        }
                    }
                }
            }
        }
    }

    delwin(win);
}



