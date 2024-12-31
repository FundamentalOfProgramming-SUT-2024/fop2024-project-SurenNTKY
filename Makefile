CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = game
SOURCES = main.c create_user.c
OBJECTS = $(SOURCES:.c=.o)


$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) -lncurses


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)



