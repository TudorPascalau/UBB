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
    server.sin_port = htons(5005);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (connect(c, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        return 1;
    }

    char buffer[1024];
    printf("Enter first numbers separated by spaces: \n");
    if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
        perror("fgets");
        close(c);
        return 1;
    }

    send(c, buffer, strlen(buffer), 0);

    printf("Enter second numbers separated by spaces: \n");
    if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
        perror("fgets");
        close(c);
        return 1;
    }

    send(c, buffer, strlen(buffer), 0);

    int n = recv(c, buffer, sizeof(buffer) - 1, 0);
    if (n < 0) {
        perror("recv");
        close(c);
        return 1;
    }
    buffer[n] = '\0';
    printf("Intersection: %s\n", buffer);

    close(c);

    return 0;
}