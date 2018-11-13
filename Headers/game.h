//
// Created by nicko on 10/04/18.
//

#ifndef TAREA_3_GAME_H
#define TAREA_3_GAME_H
#define MAX_BOMBS 5
#define HEIGHT 630
#define ENEMIGOS 50
#define BUNKERS 4

#include <stdio.h>
#include <stdlib.h>

struct player {
    int row, col;
    int vidas;
};

struct alien {
    int type; /* 1 = pulpo, 2 = cangrejo, 3 = calamar */
    int row, col;
    int value;
    int state; /* 1 = vivo, 0 = destruido */
    char* direction; /* 'l' = izq, 'r' = der */
    int speed_alien;
};

struct shoot {
    int row, col, shoot_speed, state; /* 1 = activo, 0 = inactive */
};

struct options {
    int speed_alien;
    double bombchance;

};

struct bomb {
    int row, col;
    int bomb_speed;
    int state; /*1 = active 0 = inactive*/
};

struct buncker {
    int row, col;
    int vida; /* 3 = full, 2 = medio, 1 = basico; */
    int state; /*1 = active 0 = inactive*/
};

struct state {
    struct player player1;
    struct alien aliens[ENEMIGOS];
    struct shoot bullet;
    struct options settings;
    struct bomb bombs[MAX_BOMBS];
    struct buncker bunkers[BUNKERS];
    unsigned int currentShots, currentBombs, currentAliens;
    int score, win;
};

struct state game_core();

void move_aliens(struct alien* aliens, struct options* settings,unsigned int* currentBombs, struct bomb* bombs,
                 struct player* player1);

void move_player(struct player* p1, char dir);

void move_bomb(struct bomb* bombs, struct buncker* bunkers, struct player* player1);

void move_shoots(struct shoot* shoots, struct alien* aliens, int* score);

void end_game();

void update_game(struct state* game);

void update_player(struct state* game, char* dir);

void update_shoot(struct state* game);

#endif //TAREA_3_GAME_H
