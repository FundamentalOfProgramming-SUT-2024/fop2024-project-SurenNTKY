#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "user.h"

void register_user() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MIN_LENGTH * 2];
    char email[EMAIL_MAX_LENGTH];

    WINDOW *win = newwin(12, 50, 1, 1);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Username: ");
    mvwprintw(win, 2, 1, "Password: ");
    mvwprintw(win, 3, 1, "Email: ");
    mvwprintw(win, 8, 1, "Press ESC to quit.");
    wrefresh(win);
    echo();
    int field = 0;
    int ch;

    while (1) {
        switch (field) {
            case 0:
                mvwprintw(win, 1, 13, "                           ");
                mvwgetnstr(win, 1, 13, username, USERNAME_MAX_LENGTH);
                if (username[0] == '\0') {
                    mvwprintw(win, 9, 1, "Username cannot be empty.");
                } else if (!check_username(username)) {
                    mvwprintw(win, 9, 1, "Username already exists or invalid.");
                } else {
                    field++;
                    mvwprintw(win, 9, 1, "                                 ");
                }
                break;
            case 1:
                mvwprintw(win, 2, 13, "                           ");
                mvwgetnstr(win, 2, 13, password, PASSWORD_MIN_LENGTH * 2);
                if (password[0] == '\0') {
                    mvwprintw(win, 9, 1, "Password cannot be empty.");
                } else if (!check_password(password)) {
                    mvwprintw(win, 9, 1, "Password must be at least 7 chars, including one digit, one uppercase, and one lowercase.");
                } else {
                    field++;
                    mvwprintw(win, 9, 1, "                                 ");
                }
                break;
            case 2:
                mvwprintw(win, 3, 13, "                           ");
                mvwgetnstr(win, 3, 13, email, EMAIL_MAX_LENGTH);
                if (email[0] == '\0') {
                    mvwprintw(win, 9, 1, "Email cannot be empty.");
                } else if (!check_email(email)) {
                    mvwprintw(win, 9, 1, "Invalid email format.");
                } else {
                    field++;
                    mvwprintw(win, 9, 1, "                                 ");
                }
                break;
            default:
                break;
        }

        box(win, 0, 0);
        mvwprintw(win, 1, 1, "Username: ");
        mvwprintw(win, 2, 1, "Password: ");
        mvwprintw(win, 3, 1, "Email: ");
        mvwprintw(win, 8, 1, "Press ESC to quit.");
        wrefresh(win);

        ch = getch();
        if (ch == 27) {
            break;
        } else if (ch == KEY_UP && field > 0) {
            field--;
        } else if (ch == KEY_DOWN && field < 2) {
            field++;
        }

        if (field == 3) {
            if (create_user(username, password, email)) {
                mvwprintw(win, 5, 1, "User created successfully. Press ESC to quit.");
            } else {
                mvwprintw(win, 5, 1, "Failed to create user. Press ESC to quit.");
            }
            wrefresh(win);
            getch();
            break;
        }
    }

    delwin(win);
}



