//
// Created by nicko on 10/04/18.
//

#include <iso646.h>
#include "../Headers/game.h"

/*
 * 50*30 MALOS Y JUGADOR
 * BUNKER 200*50 / 70 entre cada uno
 * 30 pix
 */

struct state game_core() {
    struct player jugador;
    struct alien  enemigos[ENEMIGOS];
    struct shoot  bullet;
    struct bomb bombs[MAX_BOMBS];
    struct buncker bunkers[BUNKERS];
    struct options settings;

    unsigned int currentShots = 0, currentBombs = 0, currentAliens = ENEMIGOS;
    int  score = 0, win = -1;

    /* se setean los ajueste */
    settings.bombchance = 2.5;
    settings.speed_alien = 10;

    /* player settings */
    jugador.row = 510;
    jugador.col = 400;
    jugador.vidas = 3;

    /* bunkers setting */
    for (int i = 0; i < 4; ++i) {
        bunkers[i].row = 400;
        bunkers[i].col = 113+160*i;
        bunkers[i].state = 1;
        bunkers[i].vida = 3;
    }

    /* aliens settings */
    int col_number = 0;
    int x = 0;
    while (col_number != 5){

        if(col_number == 0){
            for (int j = 0; j < 10; ++j) {
                enemigos[j].row = 108+35*col_number;
                enemigos[j].col = 42+55*j;
                enemigos[j].type = 1;
                enemigos[j].value = 40;
                enemigos[j].state = 1;
                enemigos[j].direction = "r";
                enemigos[j].speed_alien = settings.speed_alien;
            }
        }

        if(col_number == 1){
            for (int k = 10; k < 20; ++k) {
                enemigos[k].row = 108+35*col_number;
                enemigos[k].col = 42+55*x;
                enemigos[k].type = 1;
                enemigos[k].value = 20;
                enemigos[k].state = 1;
                enemigos[k].direction = "r";
                enemigos[k].speed_alien = settings.speed_alien;
                x++;
            }
            x = 0;
        }

        if (col_number == 2){
            for (int l = 20; l < 30; ++l) {
                enemigos[l].row = 108+35*col_number;
                enemigos[l].col = 42+55*x;
                enemigos[l].type = 1;
                enemigos[l].value = 20;
                enemigos[l].state = 1;
                enemigos[l].direction = "r";
                enemigos[l].speed_alien = settings.speed_alien;
                x++;
            }
            x = 0;
        }

        if (col_number == 3){
            for (int m = 30; m < 40; ++m) {
                enemigos[m].row = 108+35*col_number;
                enemigos[m].col = 42+55*x;
                enemigos[m].type = 1;
                enemigos[m].value = 10;
                enemigos[m].state = 1;
                enemigos[m].direction = "r";
                enemigos[m].speed_alien = settings.speed_alien;
                x++;
            }
            x = 0;
        }

        if (col_number == 4){
            for (int n = 40; n < 50; ++n) {
                enemigos[n].row = 108+35*col_number;
                enemigos[n].col = 42+55*x;
                enemigos[n].type = 1;
                enemigos[n].value = 10;
                enemigos[n].state = 1;
                enemigos[n].direction = "r";
                enemigos[n].speed_alien = settings.speed_alien;
                x++;
            }
        }

        ++col_number;
    }

    /* disparos settings */
    bullet.state = 0;
    bullet.shoot_speed = 10;

    /* bombs settings */
    for (int j1 = 0; j1 < MAX_BOMBS; ++j1) {
        bombs[j1].row = 0;
        bombs[j1].col = 0;
        bombs[j1].state = 0;
        bombs[j1].bomb_speed = 10;
    }

    struct state actual_state;

    actual_state.player1 = jugador;

    for (int k1 = 0; k1 < 50; ++k1) {
        actual_state.aliens[k1] = enemigos[k1];
    }

    actual_state.bullet = bullet;

    actual_state.settings = settings;

    for (int m1 = 0; m1 < MAX_BOMBS; ++m1) {
        actual_state.bombs[m1] = bombs[m1];
    }

    for (int n1 = 0; n1 < BUNKERS; ++n1) {
        actual_state.bunkers[n1] = bunkers[n1];
    }

    actual_state.currentAliens = currentAliens;
    actual_state.currentBombs = currentBombs;
    actual_state.currentShots = currentShots;
    actual_state.score = score;
    actual_state.win = win;

    return actual_state;
}


void move_aliens(struct alien* aliens, struct options* settings, unsigned int* currentBombs, struct bomb* bombs,
                 struct player* player1){

    int random = 0;

    if (aliens[9].col == 770 && aliens[9].direction == "r"){
        for (int i = 0; i < 50; ++i) {
            aliens[i].direction = "l";
            aliens[i].row += aliens[i].speed_alien;
            random = 1 + (rand()%100);
            if ((settings->bombchance - random) >= 0 && *currentBombs < MAX_BOMBS){
                for (int j = 0; j < MAX_BOMBS; ++j) {
                    if (not(bombs[j].state)){
                        bombs[j].state = 1;
                        ++*currentBombs;
                        bombs[j].row = aliens[i].row + 5;
                        bombs[j].col = aliens[i].col + 5;
                        break;
                    }
                }
            }
        }
    }

    if (aliens[0].col == 0 && aliens[0].direction == "l"){
        for (int i = 0; i < 50; ++i) {
            aliens[i].direction = "r";
            aliens[i].row += aliens[i].speed_alien;
            random = 1 + (rand()%100);
            if ((settings->bombchance - random) >= 0 && *currentBombs < MAX_BOMBS){
                for (int j = 0; j < MAX_BOMBS; ++j) {
                    if (not(bombs[j].state)){
                        bombs[j].state = 1;
                        ++*currentBombs;
                        bombs[j].row = aliens[i].row + 5;
                        bombs[j].col = aliens[i].col + 5;
                        break;
                    }
                }
            }
        }
    }

    if (aliens[15].direction == "r"){
        for (int i = 0; i < 50; ++i) {
            aliens[i].col += aliens[i].speed_alien;
            random = 1 + (rand()%100);
            if ((settings->bombchance - random) >= 0 && *currentBombs < MAX_BOMBS){
                for (int j = 0; j < MAX_BOMBS; ++j) {
                    if (not(bombs[j].state)){
                        bombs[j].state = 1;
                        ++*currentBombs;
                        bombs[j].row = aliens[i].row + 5;
                        bombs[j].col = aliens[i].col + 5;
                        break;
                    }
                }
            }
        }
    }

    if (aliens[15].direction == "l"){
        for (int i = 0; i < 50; ++i) {
            aliens[i].col -= aliens[i].speed_alien;
            random = 1 + (rand()%100);
            if ((settings->bombchance - random) >= 0 && *currentBombs < MAX_BOMBS){
                for (int j = 0; j < MAX_BOMBS; ++j) {
                    if (not(bombs[j].state)){
                        bombs[j].state = 1;
                        ++*currentBombs;
                        bombs[j].row = aliens[i].row + 5;
                        bombs[j].col = aliens[i].col + 5;
                        break;
                    }
                }
            }
        }
    }

    for (int k = 0; k < ENEMIGOS; ++k) {
        if ((*player1).row <= aliens[k].row){
            end_game();
        }
    }

}

void move_player(struct player* p1, char dir){
    if ((*p1).col == 0 && dir == 'l'){
        printf("izquierda maxima\n");
        return;
    }

    if ((*p1).col == 770 && dir == 'r'){
        printf("derecha maxima\n");
        return;
    }

    if (dir == 'l'){
        (*p1).col -= 10;
    }

    if (dir == 'r'){
        (*p1).col += 10;
    }
}

void move_bomb(struct bomb* bombs, struct buncker* bunkers, struct player* player1){
    for (int i = 0; i < MAX_BOMBS; ++i) {
        if (bombs[i].state){
            if (bombs[i].row < HEIGHT){
                bombs[i].row += bombs[i].bomb_speed;
            }

            for (int j = 0; j < BUNKERS; ++j) {
                if (bunkers[j].col <= bombs[i].col <= (bunkers[j].col + 200) &&
                    (bunkers[j].row <= bombs[i].row <= (bunkers[j].row + 50))){
                    if (bunkers[j].vida == 1){
                        bunkers[j].vida = 0;
                        bunkers[j].state = 0;
                        bombs[i].state = 0;
                    } else {
                        --bunkers[j].vida;
                        bombs[i].state = 0;
                    }
                }
            }

            if ((*player1).col <= bombs[i].col <= ((*player1).col + 50) &&
                (*player1).row <= bombs[i].row <= ((*player1).row + 50)){
                end_game();
            }
        }
    }
}

void move_shoots(struct shoot* bullet, struct alien* aliens, int* score){
    if ((*bullet).state){
        if ((*bullet).row > 0){
            (*bullet).row += (*bullet).shoot_speed;
        } else {
            (*bullet).state = 0;
        }

        for (int i = 0; i < ENEMIGOS; ++i) {
            if (aliens[i].state && aliens[i].row == (*bullet).row && aliens[i].col == (*bullet).col){
                *score += aliens[i].value;
                aliens[i].state = 0;
                (*bullet).state = 0;
            }
        }
    }
}

void end_game(){
    printf("se acabo el juego");
}

void update_game(struct state* game) {
    move_aliens((*game).aliens, &(game->settings), &((*game).currentBombs), (*game).bombs, &(game->player1));
    move_bomb((*game).bombs, (*game).bunkers, &(game->player1));
    move_shoots(&(game->bullet), (*game).aliens, &((*game).score));
}

void update_player(struct state* game, char* dir){
    move_aliens((*game).aliens, &(game->settings), &((*game).currentBombs), (*game).bombs, &(game->player1));
    move_player(&(game->player1), *dir);
    move_bomb((*game).bombs, (*game).bunkers, &(game->player1));
    move_shoots(&(game->bullet), (*game).aliens, &((*game).score));
}

void update_shoot(struct state* game) {
    (*game).bullet.state = 1;
    (*game).bullet.row = (*game).player1.row + 5;
    (*game).bullet.col = (*game).player1.col;
    move_aliens((*game).aliens, &(game->settings), &((*game).currentBombs), (*game).bombs, &(game->player1));
    move_bomb((*game).bombs, (*game).bunkers, &(game->player1));
    move_shoots(&(game->bullet), (*game).aliens, &((*game).score));
}