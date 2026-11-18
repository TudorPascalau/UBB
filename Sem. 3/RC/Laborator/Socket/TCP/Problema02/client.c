//Un client trimite unui server un sir de caractere. Serverul va returna clientului numarul de caractere spatiu din sir.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>


int main() {
    int c;
    struct sockaddr_in server = {0};

    c = socket(AF_INET, SOCK_STREAM, 0);
    if(c < 0) {
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    if(connect(c, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Connection failed\n");
        exit(EXIT_FAILURE);
    }

    uint16_t space_count;
    char buffer[256];

    printf("Enter a string: ");
    fgets(buffer, sizeof(buffer), stdin);

    if(send(c, buffer, strlen(buffer), 0) < 0) {
        perror("Send failed\n");
        exit(EXIT_FAILURE);
    }

    if(recv(c, &space_count, sizeof(space_count), 0) < 0) {
        perror("Receive failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Number of spaces: %u\n", space_count);

    close(c);

    return 0;
}