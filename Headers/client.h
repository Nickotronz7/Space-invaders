//
// Created by nicko on 10/04/18.
//

#ifndef TAREA_3_CLIENT_H
#define TAREA_3_CLIENT_H

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <malloc.h>
#include "cJSON.h"

void client(char* host_name, int host_port);

#endif //TAREA_3_CLIENT_H
