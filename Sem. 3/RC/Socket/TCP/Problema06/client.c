
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
    if (c < 0) {
        perror("socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(7000);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (connect(c, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        return 1;
    }

    char buffer[1024];
    printf("Enter message: \n");
    fgets(buffer, sizeof(buffer), stdin);
    send(c, buffer, strlen(buffer), 0);

    char character;
    printf("Enter a character: \n");
    scanf(" %c", &character);
    send(c, &character, sizeof(character), 0);

    int n = recv(c, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Positions of character in message: %s", buffer);
    }
    else {
        printf("No positions received.\n");
    }

    close(c);
}