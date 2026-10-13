////Un client trimite unui server un sir de caractere. Serverul va returna clientului numarul de caractere spatiu din sir.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    int s;
    struct sockaddr_in server = {0}, client = {0};
    int c, l;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0) {
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    server.sin_port = htons(8080);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Bind failed\n");
        exit(EXIT_FAILURE);
    }

    listen(s, 5);
    
    while(1) {
        l = sizeof(client);
        c = accept(s, (struct sockaddr*)&client, &l);
        printf("Client connected\n");

        char buffer[256];
        uint16_t space_count = 0;

        if(recv(c, buffer, sizeof(buffer), 0) < 0) {
            perror("Receive failed\n");
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < strlen(buffer); i++) {
            if(buffer[i] == ' ') {
                space_count++;
            }
        }

        if(send(c, &space_count, sizeof(space_count), 0) < 0) {
            perror("Send failed\n");
            exit(EXIT_FAILURE);
        }

        close(c);
    }

}