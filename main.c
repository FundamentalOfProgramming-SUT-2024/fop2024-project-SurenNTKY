#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "user.h"
#include "menu.h"


void show_menu() {
   WINDOW *menu_win;
   int highlight = 1, choice = 0, c;
   char *choices[] = {"New Game", "Continue Game", "Scoreboard", "Settings", "Profile", "Exit"};
   int n_choices = sizeof(choices) / sizeof(char *);


   clear();
   refresh();


   int max_y, max_x;
   getmaxyx(stdscr, max_y, max_x);
   int menu_height = n_choices + 4;
   int menu_width = 40;
   int start_y = (max_y - menu_height) / 2;
   int start_x = (max_x - menu_width) / 2;


   menu_win = newwin(menu_height, menu_width, start_y, start_x);
   box(menu_win, 0, 0);
   keypad(menu_win, TRUE);


   while (1) {
       for (int i = 0; i < n_choices; ++i) {
           if (highlight == i + 1) {
               wattron(menu_win, A_REVERSE);
               mvwprintw(menu_win, i + 2, 2, "%s", choices[i]);
               wattroff(menu_win, A_REVERSE);
           } else {
               mvwprintw(menu_win, i + 2, 2, "%s", choices[i]);
           }
       }
       wrefresh(menu_win);
       c = wgetch(menu_win);
       switch (c) {
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
       if (choice != 0) break;
   }


   delwin(menu_win);


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
       case 6:
           endwin();
           printf("Exiting the game...\n");
           exit(0);
           break;
   }
}


int main() {
   initscr();
   cbreak();
   noecho();
   keypad(stdscr, TRUE);


   clear();
   refresh();


   int max_y, max_x;
   getmaxyx(stdscr, max_y, max_x);


   int win_height = 20, win_width = 60;
   int start_y = (max_y - win_height) / 2;
   int start_x = (max_x - win_width) / 2;


   WINDOW *win = newwin(win_height, win_width, start_y, start_x);
   box(win, 0, 0);
   keypad(win, TRUE);


   int ch, highlight = 1;
   while (1) {
       werase(win);
       box(win, 0, 0);
       if (highlight == 1) {
           wattron(win, A_REVERSE);
           mvwprintw(win, 2, 2, "1. Login");
           wattroff(win, A_REVERSE);
       } else {
           mvwprintw(win, 2, 2, "1. Login");
       }


       if (highlight == 2) {
           wattron(win, A_REVERSE);
           mvwprintw(win, 3, 2, "2. Register");
           wattroff(win, A_REVERSE);
       } else {
           mvwprintw(win, 3, 2, "2. Register");
       }


       if (highlight == 3) {
           wattron(win, A_REVERSE);
           mvwprintw(win, 4, 2, "3. Guest");
           wattroff(win, A_REVERSE);
       } else {
           mvwprintw(win, 4, 2, "3. Guest");
       }


       if (highlight == 4) {
           wattron(win, A_REVERSE);
           mvwprintw(win, 5, 2, "4. Exit");
           wattroff(win, A_REVERSE);
       } else {
           mvwprintw(win, 5, 2, "4. Exit");
       }


       mvwprintw(win, 8, 2, "Use UP/DOWN keys to navigate. Enter to select.");
       wrefresh(win);


       ch = wgetch(win);
       switch (ch) {
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
               switch (highlight) {
                   case 1:
                       login();
                       clear();
                       refresh();
                       show_menu();
                       break;
                   case 2:
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





