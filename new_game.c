#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "menu.h"


#define MAP_WIDTH 80
#define MAP_HEIGHT 24
#define MIN_WIDTH 4
#define MAX_WIDTH 10
#define MIN_HEIGHT 4
#define MAX_HEIGHT 10
#define MAX_ROOMS 10


typedef struct {
    int x, y;
} Point;


typedef struct {
    int x, y;
    int width, height;
    int isVisible;
    int doorCount;
    Point *doors;
} Room;


typedef struct {
    int x, y;
    char symbol;
} Entity;


char map[MAP_HEIGHT][MAP_WIDTH];
Room *rooms[MAX_ROOMS];
int room_count = 0;
Entity player = {0, 0, '@'};


int randomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}


int hasOverlap(Room room1, Room room2) {
    return room1.x < room2.x + room2.width && room1.x + room1.width > room2.x &&
           room1.y < room2.y + room2.height && room1.y + room1.height > room2.y;
}


void init_map() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] = ' ';
        }
    }
}


Room *createRoom(Room **rooms, int roomsCount, int min_x, int min_y, int max_x, int max_y) {
    Room *room = (Room *)malloc(sizeof(Room));


    int validPlacement;
    do {
        validPlacement = 1;
        room->width = randomNumber(MIN_WIDTH, MAX_WIDTH);
        room->height = randomNumber(MIN_HEIGHT, MAX_HEIGHT);
        room->x = randomNumber(min_x, max_x - room->width);
        room->y = randomNumber(min_y, max_y - room->height);
        for (int i = 0; i < roomsCount; i++) {
            if (hasOverlap(*room, *rooms[i])) {
                validPlacement = 0;
                break;
            }
        }
    } while (!validPlacement);
    room->isVisible = 0;
    room->doorCount = 2;
    room->doors = (Point *)malloc(sizeof(Point) * room->doorCount);
    for (int i = 0; i < room->doorCount; i++) {
        if (i % 2 == 0) {
            room->doors[i].x = room->x + 1 + randomNumber(0, room->width - 2);
            room->doors[i].y = room->y + room->height - 1;
        } else {
            room->doors[i].x = room->x + 1 + randomNumber(0, room->width - 2);
            room->doors[i].y = room->y + 1;
        }
    }
    return room;
}


void create_corridor(Room *r1, Room *r2) {
    int x1 = r1->doors[0].x;
    int y1 = r1->doors[0].y;
    int x2 = r2->doors[1].x;
    int y2 = r2->doors[1].y;


    while (x1 != x2) {
        map[y1][x1] = '#';
        x1 += (x2 > x1) ? 1 : -1;
    }


    while (y1 != y2) {
        map[y1][x1] = '#';
        y1 += (y2 > y1) ? 1 : -1;
    }
}


void generate_map() {
    init_map();


    srand(time(NULL));
    for (int i = 0; i < MAX_ROOMS; i++) {
        Room *room = createRoom(rooms, room_count, 0, 0, MAP_WIDTH, MAP_HEIGHT);
        rooms[room_count++] = room;


        for (int y = room->y; y < room->y + room->height; y++) {
            for (int x = room->x; x < room->x + room->width; x++) {
                if (y == room->y || y == room->y + room->height - 1) {
                    map[y][x] = '_';
                } else if (x == room->x || x == room->x + room->width - 1) {
                    map[y][x] = '|';
                } else {
                    map[y][x] = '.';
                }
            }
        }


        for (int j = 0; j < room->doorCount; j++) {
            map[room->doors[j].y][room->doors[j].x] = '#';
        }


        if (room_count > 1) {
            create_corridor(rooms[room_count - 2], rooms[room_count - 1]);
        }
    }
}


void print_map() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            printw("%c", map[y][x]);
        }
        printw("\n");
    }
}


void place_player() {
    player.x = rooms[0]->x + rooms[0]->width / 2;
    player.y = rooms[0]->y + rooms[0]->height / 2;
}


void draw_player() {
    mvprintw(player.y, player.x, "%c", player.symbol);
}


void move_player(int dx, int dy) {
    int new_x = player.x + dx;
    int new_y = player.y + dy;


    if (map[new_y][new_x] == '.' || map[new_y][new_x] == '#') {
        player.x = new_x;
        player.y = new_y;
    }
}


void new_game() {
    generate_map();
    place_player();


    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);


    while (1) {
        clear();
        print_map();
        draw_player();
        refresh();


        int ch = getch();
        switch (ch) {
            case KEY_UP:
                move_player(0, -1);
                break;
            case KEY_DOWN:
                move_player(0, 1);
                break;
            case KEY_LEFT:
                move_player(-1, 0);
                break;
            case KEY_RIGHT:
                move_player(1, 0);
                break;
            case 'q':
                endwin();
                printf("Exiting the game...\n");
                return;
        }
    }
}







