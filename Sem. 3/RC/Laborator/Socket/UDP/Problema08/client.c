// Un client trimite unui server doua numere reprezentate pe doi octeti fara semn fiecare. Serverul va returna clientului cmmdc si cmmmc al numerelor primite.
// Se comunica prin UDP.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in server_addr = {0};

    unsigned short num1, num2;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5005);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Introduceti primul numar: ");
    scanf("%hu", &num1);
    num1 = htons(num1);

    printf("Introduceti al doilea numar: ");
    scanf("%hu", &num2);
    num2 = htons(num2);

    sendto(sock, &num1, sizeof(num1), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    sendto(sock, &num2, sizeof(num2), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, NULL, NULL);
    if (n < 0) {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("Raspuns de la server: %s\n", buffer);

    close(sock);
    return 0;
}
