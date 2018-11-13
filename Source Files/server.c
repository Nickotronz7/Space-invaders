//
// Created by nicko on 10/04/18.
//

#include "../Headers/server.h"
#include "../Headers/json_builder.h"

void* socketHandler(void*);
struct sockaddr_in sadr;

void server(int host_port) {
    struct sockaddr_in my_addr;
    int hsock;
    int* p_int;
    int err;
    socklen_t  addr_size = 0;
    int* csock;

    pthread_t thread_id=0;


    hsock = socket(AF_INET, SOCK_STREAM, 0);
    if(hsock == -1){
        printf("Error iniciando el socket %d\n", errno);
        goto FINISH;
    }

    p_int = (int*)malloc(sizeof(int));
    *p_int = 1;

    if( (setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
        (setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ){
        printf("Error al setear las opciones %d\n", errno);
        free(p_int);
        goto FINISH;
    }
    free(p_int);

    my_addr.sin_family = AF_INET ;
    my_addr.sin_port = htons(host_port);

    memset(&(my_addr.sin_zero), 0, 8);
    my_addr.sin_addr.s_addr = INADDR_ANY ;

    if( bind( hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1 ){
        fprintf(stderr,"Error uniendo al socket, asegurece de que el puerto esta libre %d\n",errno);
        goto FINISH;
    }
    if(listen( hsock, 10) == -1 ){
        fprintf(stderr, "Error al escuchar %d\n",errno);
        goto FINISH;
    }

    //Now lets do the Server stuff

    addr_size = sizeof(struct sockaddr_in);

    while(true){
        printf("Esperando una connecion escuchando %i port\n", host_port);
        csock = (int*)malloc(sizeof(int));
        if((*csock = accept( hsock, (struct sockaddr*)&sadr, &addr_size))!= -1){
            printf("---------------------\nConexion recivida de  %s\n",
                   inet_ntoa(sadr.sin_addr));
            pthread_create(&thread_id,0,&socketHandler, (void*)csock );
            pthread_detach(thread_id);
        }
        else{
            fprintf(stderr, "Error al aceptar conexion %d\n", errno);
        }
    }

    FINISH:
    ;
}

void* socketHandler(void* lp){
    int *csock = (int*)lp;

    int buffer_len = 1024;
    int respuesta_len = 7602;
    char respuesta[respuesta_len];
    char buffer[buffer_len];
    int bytecount;

    memset(buffer, '\0', buffer_len);

    if((bytecount = recv(*csock, buffer, buffer_len, 0))== -1){
        fprintf(stderr, "Error al recivir data %d\n", errno);
        //goto FINISH;
    }

    //printf("Bytes recividos %d\nMensaje recivido \"%s\"\nDe %s\n", bytecount, buffer,inet_ntoa(sadr.sin_addr));
    //strcat(buffer, " SERVER ECHO");

    char* msg = (char*)malloc(strlen(buffer));
    for (int i = 0; i < strlen(buffer); ++i) {
        *(msg+i) = buffer[i];
    }

    char* resp = analyze_msg(msg);
    for (int j = 0; j < respuesta_len; ++j) {
        respuesta[j] = *(resp+j);
    }

    free(msg);


    if((bytecount = send(*csock, resp, strlen(resp), 0))== -1){
        fprintf(stderr, "Error al responder data %d\n", errno);
        goto FINISH;
    }


    printf("%s\n", resp);
    printf("Sent bytes %d\n", bytecount);


    FINISH:
    free(csock);
}

char* analyze_msg(char* msg){
    cJSON* root = cJSON_Parse(msg);
    cJSON* respuesta = NULL;
    char* respuesta_STRING;

    char* message_type = cJSON_GetObjectItem(root, "message_type")->valuestring;

    if (strcmp(message_type, "get_update") == 0){
        update_game(&game);
        respuesta = game_state(&game);
        respuesta_STRING = cJSON_Print(respuesta);
        return respuesta_STRING;
    }

    if (strcmp(message_type, "player_move") == 0){
        char* move = cJSON_GetObjectItem(root, "move")->valuestring;
        update_player(&game, move);
        respuesta = game_state(&game);
        respuesta_STRING = cJSON_Print(respuesta);
        return respuesta_STRING;
    }

    if (strcmp(message_type, "begin_game") == 0){
        game = game_core();
        respuesta = game_state(&game);
        respuesta_STRING = cJSON_Print(respuesta);
        return respuesta_STRING;
    }

    if (strcmp(message_type, "player_shoot") == 0){
        update_shoot(&game);
        respuesta = game_state(&game);
        respuesta_STRING = cJSON_Print(respuesta);
        return respuesta_STRING;
    }

    if (strcmp(message_type, "watch_game") == 0){
        update_game(&game);
        respuesta = game_state(&game);
        respuesta_STRING = cJSON_Print(respuesta);
        return respuesta_STRING;
    }

}