//
// Created by nicko on 10/04/18.
//

#include "../Headers/json_builder.h"

cJSON* game_state(struct state* game){

    cJSON* root = cJSON_CreateObject();
    cJSON* player = game_player(&(game->player1));
    cJSON* aliens = game_aliens(game->aliens);
    cJSON* bullet = game_shoot(&(game->bullet));
    cJSON* settings = game_options(&(game->settings));
    cJSON* bombs = game_bombs(game->bombs);
    cJSON* bunkers = game_bunker(game->bunkers);
    cJSON* data = game_data(&(game->currentShots), &(game->currentBombs), &(game->currentAliens), &(game->score),
                            &(game->win));

    cJSON_AddItemToObject(root, "player", player);
    cJSON_AddItemToObject(root, "aliens", aliens);
    cJSON_AddItemToObject(root, "bullet", bullet);
    cJSON_AddItemToObject(root, "settings", settings);
    cJSON_AddItemToObject(root, "bombs", bombs);
    cJSON_AddItemToObject(root, "bunkers", bunkers);
    cJSON_AddItemToObject(root, "data", data);

    return  root;
}

cJSON* game_player(struct player* player1){
    cJSON* root = cJSON_CreateObject();

    cJSON* row = cJSON_CreateNumber((*player1).row);
    cJSON* col = cJSON_CreateNumber((*player1).col);
    cJSON* lives = cJSON_CreateNumber((*player1).vidas);


    cJSON_AddItemToObject(root, "row", row);
    cJSON_AddItemToObject(root, "col", col);
    cJSON_AddItemToObject(root, "vidas", lives);

    return root;

}

cJSON* game_aliens(struct alien* aliens){
    cJSON* root = cJSON_CreateObject();
    cJSON* alien_Array = cJSON_CreateArray();
    cJSON* alien = NULL;
    cJSON_AddItemToObject(root, "aliens", alien_Array);
    for (int i = 0; i < ENEMIGOS; ++i) {
        alien = cJSON_CreateObject();
        cJSON_AddItemToArray(alien_Array, alien);
        cJSON* type = cJSON_CreateNumber(aliens[i].type);
        cJSON* row = cJSON_CreateNumber(aliens[i].row);
        cJSON* col = cJSON_CreateNumber(aliens[i].col);
        cJSON* value = cJSON_CreateNumber(aliens[i].value);
        cJSON* state = cJSON_CreateNumber(aliens[i].state);
        cJSON* direction = cJSON_CreateString(aliens[i].direction);
        cJSON* speed_alien = cJSON_CreateNumber(aliens[i].speed_alien);

        cJSON_AddItemToObject(alien, "type", type);
        cJSON_AddItemToObject(alien, "row", row);
        cJSON_AddItemToObject(alien, "col", col);
        cJSON_AddItemToObject(alien, "value", value);
        cJSON_AddItemToObject(alien, "state", state);
        cJSON_AddItemToObject(alien, "direction", direction);
        cJSON_AddItemToObject(alien, "speed_alien", speed_alien);
    }

    return root;
}

cJSON* game_shoot(struct shoot* bullet){
    cJSON* root = cJSON_CreateObject();

    cJSON* row = cJSON_CreateNumber((*bullet).row);
    cJSON* col = cJSON_CreateNumber((*bullet).col);
    cJSON* shoot_speed = cJSON_CreateNumber((*bullet).shoot_speed);
    cJSON* state = cJSON_CreateNumber((*bullet).state);

    cJSON_AddItemToObject(root, "row", row);
    cJSON_AddItemToObject(root, "col", col);
    cJSON_AddItemToObject(root, "shoot_speed", shoot_speed);
    cJSON_AddItemToObject(root, "state", state);

    return root;
}

cJSON* game_options(struct options* settings){
    cJSON* root = cJSON_CreateObject();

    cJSON* speed_alien = cJSON_CreateNumber((*settings).speed_alien);
    cJSON* bombchance = cJSON_CreateNumber((*settings).bombchance);

    cJSON_AddItemToObject(root, "speed_alien", speed_alien);
    cJSON_AddItemToObject(root, "bombChance", bombchance);

    return root;
}

cJSON* game_bombs(struct bomb* bombs){
    cJSON* root = cJSON_CreateObject();
    cJSON* bomb_array = cJSON_CreateArray();
    cJSON* bomb = NULL;
    cJSON_AddItemToObject(root, "bombs", bomb_array);
    for (int i = 0; i < MAX_BOMBS; ++i) {
        bomb = cJSON_CreateObject();
        cJSON_AddItemToArray(bomb_array,bomb);
        cJSON* row = cJSON_CreateNumber(bombs[i].row);
        cJSON* col = cJSON_CreateNumber(bombs[i].col);
        cJSON* bomb_speed = cJSON_CreateNumber(bombs[i].bomb_speed);
        cJSON* state = cJSON_CreateNumber(bombs[i].state);

        cJSON_AddItemToObject(bomb, "row", row);
        cJSON_AddItemToObject(bomb, "col", col);
        cJSON_AddItemToObject(bomb, "speed", bomb_speed);
        cJSON_AddItemToObject(bomb, "state", state);
    }

    return root;
}

cJSON* game_bunker(struct buncker* bunkers){
    cJSON* root = cJSON_CreateObject();
    cJSON* bunker_array = cJSON_CreateArray();
    cJSON* bunker = NULL;
    cJSON_AddItemToObject(root, "bunkers", bunker_array);
    for (int i = 0; i < BUNKERS; ++i) {
        bunker = cJSON_CreateObject();
        cJSON_AddItemToArray(bunker_array, bunker);
        cJSON* row = cJSON_CreateNumber(bunkers[i].row);
        cJSON* col = cJSON_CreateNumber(bunkers[i].col);
        cJSON* vida = cJSON_CreateNumber(bunkers[i].vida);
        cJSON* state = cJSON_CreateNumber(bunkers[i].state);

        cJSON_AddItemToObject(bunker, "row", row);
        cJSON_AddItemToObject(bunker, "col", col);
        cJSON_AddItemToObject(bunker, "vida", vida);
        cJSON_AddItemToObject(bunker, "state", state);
    }

    return root;
}

cJSON* game_data(unsigned int* currentShots,unsigned int* currentBombs, unsigned int* currentAliens, int* score,
                 int* win){
    cJSON* root = cJSON_CreateObject();

    cJSON* cShots = cJSON_CreateNumber(*currentShots);
    cJSON* cBombs = cJSON_CreateNumber(*currentBombs);
    cJSON* cAliens = cJSON_CreateNumber(*currentAliens);
    cJSON* points = cJSON_CreateNumber(*score);
    cJSON* cWin = cJSON_CreateNumber(*win);

    cJSON_AddItemToObject(root,"currentShots", cShots);
    cJSON_AddItemToObject(root, "currenteBombs", cBombs);
    cJSON_AddItemToObject(root, "currentAliens", cAliens);
    cJSON_AddItemToObject(root, "score", points);
    cJSON_AddItemToObject(root, "win", cWin);

    return root;
}