#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>


int main() {
    int c;
    struct sockaddr_in server;
    uint16_t a, b, suma;

    c = socket(AF_INET, SOCK_STREAM, 0);
    if(c < 0) {
        printf("Error creating socket\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if(connect(c, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Error connecting to server\n");
        return 1;
    }

    printf("a = ");
    scanf("%hu", &a);
    printf("b = ");
    scanf("%hu", &b);

    a = htons(a);
    b = htons(b);
    send(c, &a, sizeof(a), 0);
    send(c, &b, sizeof(b), 0);

    recv(c, &suma, sizeof(suma), MSG_WAITALL);
    suma = ntohs(suma);
    printf("Sum received from server: %hu\n", suma);

    close(c);
}