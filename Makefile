CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = game
SOURCES = main.c create_user.c guest.c register_user.c login.c new_game.c continue_game.c scoreboard.c settings.c profile.c 
OBJECTS = $(SOURCES:.c=.o)


$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) -lncurses


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)



