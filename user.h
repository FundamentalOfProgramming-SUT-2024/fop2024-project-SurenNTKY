#ifndef USER_H
#define USER_H

#define USERNAME_MAX_LENGTH 30
#define PASSWORD_MIN_LENGTH 7
#define EMAIL_MAX_LENGTH 50

int check_username(const char *username);
int check_password(const char *password);
int check_email(const char *email);
int create_user(const char *username, const char *password, const char *email);
void generate_random_password(char *password);

#endif 


