// Un client trimite unui server o cerere prin care ii cere acestuia data si ora curenta. 
// Serverul va returna clientului data sub forma unui intreg ce reprezinta numarul de secunde trecute de la 1 ianuarie 1970. Clientul va afisa corespunzator data pe baza acestui intreg.
// Se comunica prin UDP.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

int main() {
    int sock;
    struct sockaddr_in server_addr = {0};

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5005);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char buffer[1024];
    sendto(sock, "request", strlen("request"), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    socklen_t addr_len = sizeof(server_addr);
    int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&server_addr, &addr_len);
    if (n < 0) {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    long timestamp = atol(buffer);
    printf("Received timestamp: %ld\n", timestamp);
    printf("Date and time: %s", ctime(&timestamp));

    close(sock);
    return 0;
}

