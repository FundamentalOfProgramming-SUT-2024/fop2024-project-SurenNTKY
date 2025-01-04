#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "user.h"
#include "menu.h"

void show_menu()
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_BLUE);

    int highlight = 1, choice = 0, c;
    char *choices[] = {"New Game", "Continue Game", "Scoreboard", "Settings", "Profile", "Exit"};
    int n_choices = sizeof(choices) / sizeof(char *);

    clear();
    refresh();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int menu_height = 20;
    int menu_width = 60;
    int start_y = (max_y - menu_height) / 2;
    int start_x = (max_x - menu_width) / 2;

    WINDOW *menu_win = newwin(menu_height, menu_width, start_y, start_x);
    box(menu_win, 0, 0);
    wbkgd(menu_win, COLOR_PAIR(1));

    int max_y1, max_x1;
    getmaxyx(stdscr, max_y1, max_x1);
    int menu_height1 = 22;
    int menu_width1 = 62;
    int start_y1 = (max_y1 - menu_height1) / 2;
    int start_x1 = (max_x1 - menu_width1) / 2;

    WINDOW *menu_win1 = newwin(menu_height1, menu_width1, start_y1, start_x1);
    box(menu_win1, 0, 0);
    wbkgd(menu_win1, COLOR_PAIR(2));

    keypad(menu_win, TRUE);

    while (1)
    {

        if (highlight == 1)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, 2, 26, "NEW GAME");
            wattroff(menu_win, A_REVERSE);
        }
        else
        {
            mvwprintw(menu_win, 2, 26, "NEW GAME");
        }
        if (highlight == 2)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, 5, 23.5, "CONTINUE GAME");
            wattroff(menu_win, A_REVERSE);
        }
        else
        {
            mvwprintw(menu_win, 5, 23.5, "CONTINUE GAME");
        }
        if (highlight == 3)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, 8, 25, "SCOREBOARD");
            wattroff(menu_win, A_REVERSE);
        }
        else
        {
            mvwprintw(menu_win, 8, 25, "SCOREBOARD");
        }
        if (highlight == 4)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, 11, 26, "SETTINGS");
            wattroff(menu_win, A_REVERSE);
        }
        else
        {
            mvwprintw(menu_win, 11, 26, "SETTINGS");
        }
        if (highlight == 5)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, 14, 26.5, "PROFILE");
            wattroff(menu_win, A_REVERSE);
        }
        else
        {
            mvwprintw(menu_win, 14, 26.5, "PROFILE");
        }
        if (highlight == 6)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, 17, 28, "EXIT");
            wattroff(menu_win, A_REVERSE);
        }
        else
        {
            mvwprintw(menu_win, 17, 28, "EXIT");
        }

        wrefresh(menu_win1);
        wrefresh(menu_win);
        c = wgetch(menu_win);
        switch (c)
        {
        case KEY_UP:
            highlight = (highlight == 1) ? n_choices : highlight - 1;
            break;
        case KEY_DOWN:
            highlight = (highlight == n_choices) ? 1 : highlight + 1;
            break;
        case 10:
            choice = highlight;
            break;
        }
        if (choice != 0)
            break;
    }

    delwin(menu_win);

    switch (choice)
    {
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
    case 6:
        int max_y2, max_x2;
        getmaxyx(stdscr, max_y2, max_x2);
        int menu_height2 = 5;
        int menu_width2 = 70;
        int start_y2 = (max_y2 - menu_height2) / 2;
        int start_x2 = (max_x2 - menu_width2) / 2;

        WINDOW *menu_win2 = newwin(menu_height2, menu_width2, start_y2, start_x2);
        box(menu_win2, 0, 0);
        wbkgd(menu_win2, COLOR_BLACK);
        attron(A_BOLD);
        attron(COLOR_RED);
        mvwprintw(menu_win2, 2.5, 25.5, "Exiting the game...");
        wrefresh(menu_win2);
        napms(2000);
        endwin();
        exit(0);
        break;
    }
}

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();

    clear();
    refresh();

    int max_y1, max_x1;
    getmaxyx(stdscr, max_y1, max_x1);

    int win_height1 = 22, win_width1 = 62;
    int start_y1 = (max_y1 - win_height1) / 2;
    int start_x1 = (max_x1 - win_width1) / 2;

    WINDOW *win1 = newwin(win_height1, win_width1, start_y1, start_x1);
    box(win1, 0, 0);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int win_height = 20, win_width = 60;
    int start_y = (max_y - win_height) / 2;
    int start_x = (max_x - win_width) / 2;

    WINDOW *win = newwin(win_height, win_width, start_y, start_x);
    box(win, 0, 0);

    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_CYAN);

    keypad(win, TRUE);
    keypad(win1, TRUE);

    int ch, highlight = 1;
    while (1)
    {
        werase(win);
        werase(win1);
        box(win1, 0, 0);
        box(win, 0, 0);
        wbkgd(win1, COLOR_PAIR(1));
        wbkgd(win, COLOR_PAIR(2));
        if (highlight == 1)
        {
            wattron(win, A_REVERSE);
            mvwprintw(win, 6, 27, "Login");
            wattroff(win, A_REVERSE);
        }
        else
        {
            mvwprintw(win, 6, 27, "Login");
        }

        if (highlight == 2)
        {
            wattron(win, A_REVERSE);
            mvwprintw(win, 8, 26, "Register");
            wattroff(win, A_REVERSE);
        }
        else
        {
            mvwprintw(win, 8, 26, "Register");
        }

        if (highlight == 3)
        {
            wattron(win, A_REVERSE);
            mvwprintw(win, 10, 27.5, "Guest");
            wattroff(win, A_REVERSE);
        }
        else
        {
            mvwprintw(win, 10, 27.5, "Guest");
        }

        if (highlight == 4)
        {
            wattron(win, A_REVERSE);
            mvwprintw(win, 12, 28, "Exit");
            wattroff(win, A_REVERSE);
        }
        else
        {
            mvwprintw(win, 12, 28, "Exit");
        }

        mvwprintw(win, 2, 23.5, "W E L C O M E");
        curs_set(0);

        wrefresh(win1);
        wrefresh(win);

        ch = wgetch(win);
        switch (ch)
        {
        case KEY_UP:
            highlight = (highlight == 1) ? 4 : highlight - 1;
            break;
        case KEY_DOWN:
            highlight = (highlight == 4) ? 1 : highlight + 1;
            break;
        case 10:
            delwin(win);
            clear();
            refresh();
            switch (highlight)
            {
            case 1:
                curs_set(1);
                login();
                clear();
                refresh();
                show_menu();
                break;
            case 2:
                curs_set(1);
                register_user();
                clear();
                refresh();
                show_menu();
                break;
            case 3:
                guest();
                clear();
                refresh();
                show_menu();
                break;
            case 4:
                endwin();
                printf("Exiting the game...\n");
                return 0;
            }
            break;
        }
    }

    endwin();
    return 0;
}
