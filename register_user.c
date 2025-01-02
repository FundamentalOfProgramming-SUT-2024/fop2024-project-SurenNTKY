#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "user.h"


#define USERNAME_MAX_LENGTH 30
#define PASSWORD_MIN_LENGTH 7
#define EMAIL_MAX_LENGTH 50


void register_user() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MIN_LENGTH * 2];
    char email[EMAIL_MAX_LENGTH];
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int win_height = 20, win_width = 50;
    int start_y = (max_y - win_height) / 2;
    int start_x = (max_x - win_width) / 2;


    WINDOW *win = newwin(win_height, win_width, start_y, start_x);
    box(win, 0, 0);
    keypad(win, TRUE);


    mvwprintw(win, 1, 1, "Username: ");
    mvwprintw(win, 2, 1, "Password: ");
    mvwprintw(win, 3, 1, "Email: ");
    wrefresh(win);
    echo();
    int field = 0;
    MEVENT event;
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);


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
                    mvwprintw(win, 9, 1, "                                  ");
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
                    mvwprintw(win, 9, 1, "                                                                                          ");
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
        wrefresh(win);


        mvwprintw(win, 5, 1, "Confirm");
        mvwprintw(win, 5, 15, "Exit");
        wrefresh(win);


        int ch = getch();
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_CLICKED) {
                    if (event.y == start_y + 5 && event.x >= start_x + 1 && event.x <= start_x + 8) { // Confirm button
                        if (field == 3) {
                            if (create_user(username, password, email)) {
                                mvwprintw(win, 6, 1, "User created successfully.");
                            } else {
                                mvwprintw(win, 6, 1, "Failed to create user.");
                            }
                            wrefresh(win);
                            getch();
                            break;
                        }
                    } else if (event.y == start_y + 5 && event.x >= start_x + 15 && event.x <= start_x + 21) { // Exit button
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







