//
// Created by nicko on 10/04/18.
//

#ifndef TAREA_3_SERVER_H
#define TAREA_3_SERVER_H

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <malloc.h>
#include <stdbool.h>
#include "cJSON.h"
#include "cJSON_Utils.h"
#include "game.h"


void server(int host_port);

char* analyze_msg(char* msg);

struct state game;

void* socketHandler(void*);

#endif //TAREA_3_SERVER_H
