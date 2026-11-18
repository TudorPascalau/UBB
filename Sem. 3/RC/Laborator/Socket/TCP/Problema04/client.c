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
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(c, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        return 1;
    }

    char str1[100], str2[100];
    printf("Enter first sorted string: ");
    scanf("%s", str1);
    printf("Enter second sorted string: ");
    scanf("%s", str2);

    char message[200];
    snprintf(message, sizeof(message), "%s %s", str1, str2);
    send(c, message, strlen(message), 0);

    char buffer[1024];
    int n = recv(c, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Interleaved string: %s\n", buffer);
    }

    close(c);
}