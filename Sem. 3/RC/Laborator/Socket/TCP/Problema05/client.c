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

    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%d", n);
    send(c, buffer, strlen(buffer), 0);

    int m = recv(c, buffer, sizeof(buffer) - 1, 0);
    if (m > 0) {
        buffer[m] = '\0';
        printf("Number of divisors: %s\n", buffer);
    }

    m = recv(c, buffer, sizeof(buffer) - 1, 0);
    if (m > 0) {
        buffer[m] = '\0';
        printf("Divisors: %s\n", buffer);
    }

    close(c);
}