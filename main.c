#include <stdio.h>
#include <ncurses.h>
#include "user.h"
#include "game.h"

void show_menu() {
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    char *choices[] = {
        "New Game",
        "Continue Game",
        "Scoreboard",
        "Settings",
        "Profile"
    };
    int n_choices = sizeof(choices) / sizeof(char *);

    menu_win = newwin(10, 40, 4, 4);
    keypad(menu_win, TRUE);
    
    while (1) {
        for (int i = 0; i < n_choices; ++i) {
            if (highlight == i + 1) {
                wattron(menu_win, A_REVERSE);
                mvwprintw(menu_win, i + 1, 1, "%s", choices[i]);
                wattroff(menu_win, A_REVERSE);
            } else {
                mvwprintw(menu_win, i + 1, 1, "%s", choices[i]);
            }
        }
        wrefresh(menu_win);
        c = wgetch(menu_win);
        
        switch (c) {
            case KEY_UP:
                if (highlight == 1) highlight = n_choices;
                else --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_choices) highlight = 1;
                else ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        if (choice != 0) break;
    }
    
    switch (choice) {
        case 1:
            new_game();
            break;
        case 2:
            continue_game();
            break;
        case 3:
            show_scoreboard();
            break;
        case 4:
            show_settings();
            break;
        case 5:
            show_profile();
            break;
    }

    delwin(menu_win);
}

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

    int ch;
    while (1) {
        werase(win);
        box(win, 0, 0);
        mvwprintw(win, 1, 1, "1. Login");
        mvwprintw(win, 2, 1, "2. Register");
        mvwprintw(win, 3, 1, "3. Guest");
        mvwprintw(win, 8, 1, "Press the corresponding number to choose.");
        wrefresh(win);
        ch = getch();
        if (ch == '1' || ch == '2' || ch == '3') {
            break;
        }
    }

    delwin(win);

    switch (ch) {
        case '1':
            login();
            show_menu();
            break;
        case '2':
            register_user();
            show_menu();
            break;
        case '3':
            guest();
            show_menu();
            break;
        default:
            break;
    }

    endwin();
    return 0;
}


