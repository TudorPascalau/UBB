#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

int main() {
    int s;
    struct sockaddr_in server, client;
    int c, l;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0) {
        printf("Error creating socket\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Error binding socket\n");
        return 1;
    }

    listen(s, 5);

    l = sizeof(client);
    memset(&client, 0, sizeof(client));

    while(1) {
        uint16_t a, b, suma;
        c = accept(s, (struct sockaddr*)&client, &l);
        printf("Client connected\n");

        recv(c, &a, sizeof(a), MSG_WAITALL);
        recv(c, &b, sizeof(b), MSG_WAITALL);

        a = ntohs(a);
        b = ntohs(b);

        printf("Received numbers: %d, %d\n", a, b);

        suma = a + b;
        suma = htons(suma);
        send(c, &suma, sizeof(suma), 0);
        close(c);
    }
}