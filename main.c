#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "user.h"

void get_input(WINDOW *win, int start_y, int start_x, char *str, int n) {
   mvwgetnstr(win, start_y, start_x, str, n);
}

void show_error(WINDOW *win, const char *message) {
   mvwprintw(win, 9, 1, message);  
   wrefresh(win);
}

int main() {
   initscr();
   echo();
   cbreak();
   keypad(stdscr, TRUE);

   WINDOW *win = newwin(12, 50, 1, 1);
   box(win, 0, 0);
   mvwprintw(win, 1, 1, "Username: ");
   mvwprintw(win, 2, 1, "Password: ");
   mvwprintw(win, 3, 1, "Email: ");
   mvwprintw(win, 8, 1, "Press 'q' to quit.");
   wrefresh(win);

   char username[USERNAME_MAX_LENGTH];
   char password[PASSWORD_MIN_LENGTH * 2];
   char email[EMAIL_MAX_LENGTH];

   int field = 0;
   int ch;

   while (1) {
       switch (field) {
           case 0:
               mvwprintw(win, 1, 13, "                           ");
               get_input(win, 1, 13, username, USERNAME_MAX_LENGTH);
               if (username[0] == '\0') {
                   show_error(win, "Username cannot be empty.");
               } else if (!check_username(username)) {
                   show_error(win, "Username already exists or invalid.");
               } else {
                   field++;
               }
               break;
           case 1:
               mvwprintw(win, 2, 13, "                           ");
               get_input(win, 2, 13, password, PASSWORD_MIN_LENGTH * 2);
               if (password[0] == '\0') {
                   show_error(win, "Password cannot be empty.");
               } else if (!check_password(password)) {
                   show_error(win, "Password must be at least 7 chars, including one digit, one uppercase, and one lowercase.");
               } else {
                   field++;
               }
               break;
           case 2:
               mvwprintw(win, 3, 13, "                           ");
               get_input(win, 3, 13, email, EMAIL_MAX_LENGTH);
               if (email[0] == '\0') {
                   show_error(win, "Email cannot be empty.");
               } else if (!check_email(email)) {
                   show_error(win, "Invalid email format.");
               } else {
                   field++;
               }
               break;
           default:
               break;
       }

       box(win, 0, 0);
       mvwprintw(win, 1, 1, "Username: ");
       mvwprintw(win, 2, 1, "Password: ");
       mvwprintw(win, 3, 1, "Email: ");
       mvwprintw(win, 8, 1, "Press 'q' to quit.");
       wrefresh(win);

       ch = getch();
       if (ch == 'q' || ch == 27) {
           break;
       } else if (ch == KEY_UP && field > 0) {
           field--;
       } else if (ch == KEY_DOWN && field < 2) {
           field++;
       }

       if (field == 3) {
           if (create_user(username, password, email)) {
               mvwprintw(win, 5, 1, "User created successfully. Press 'q' to quit.");
           } else {
               mvwprintw(win, 5, 1, "Failed to create user. Press 'q' to quit.");
           }
           wrefresh(win);
           getch();
           break;
       }
   }

   endwin();
   return 0;
}



