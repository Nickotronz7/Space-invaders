//
// Created by nicko on 10/04/18.
//

#include "../Headers/client.h"

void client(char* host_name, int host_port){

    struct sockaddr_in my_addr;

    int buffer_len = 48;
    char* buffer;
    int bytecount;

    int hsock;
    int * p_int;
    int err;

    hsock = socket(AF_INET, SOCK_STREAM, 0);
    if(hsock == -1){
        printf("Error initializing socket %d\n",errno);
        goto FINISH;
    }

    p_int = (int*)malloc(sizeof(int));
    *p_int = 1;

    if( (setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
        (setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ){
        printf("Error setting options %d\n",errno);
        free(p_int);
        goto FINISH;
    }
    free(p_int);

    my_addr.sin_family = AF_INET ;
    my_addr.sin_port = htons(host_port);

    memset(&(my_addr.sin_zero), 0, 8);
    my_addr.sin_addr.s_addr = inet_addr(host_name);

    if( connect( hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1 ){
        if((err = errno) != EINPROGRESS){
            fprintf(stderr, "Error connecting socket %d\n", errno);
            goto FINISH;
        }
    }
    //Now lets do the client related stuff
    /*
    memset(buffer, '\0', buffer_len);
    printf("Enter some text to send to the server (press enter)\n");
    fgets(buffer, 1024, stdin);
    puts(buffer);
    */
    cJSON* root = cJSON_CreateObject();
    cJSON* message_type1 = cJSON_CreateString("begin_game");
    cJSON_AddItemToObject(root, "message_type", message_type1);
    buffer = cJSON_Print(root);
    //buffer[strlen(buffer) - 1] = '\0';

    if( (bytecount=send(hsock, buffer, strlen(buffer),0))== -1){
        fprintf(stderr, "Error sending data %d\n", errno);
        goto FINISH;
    }
    printf("Sent bytes %d\n", bytecount);

    char resp[7602];
    if((bytecount = recv(hsock, resp, 7602, 0))== -1){
        fprintf(stderr, "Error receiving data %d\n", errno);
        goto FINISH;
    }
    printf("Recieved bytes %d\nReceived string \"%s\"\n", bytecount, resp);
    close(hsock);
    FINISH:;
}