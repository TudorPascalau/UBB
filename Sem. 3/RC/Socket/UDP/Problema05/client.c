// Un client trimite unui server un numar reprezentat pe un octet fara semn. 
// Serverul va returna clientului sirul divizorilor acestui numar.
// Se comunica prin UDP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int c;
    c = socket(AF_INET, SOCK_DGRAM, 0);
    if (c < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2020);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    unsigned char number;
    printf("Enter a number (0-255): ");
    scanf("%hhu", &number);
    sendto(c, &number, sizeof(number), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    char buffer[101];
    socklen_t addr_len = sizeof(server_addr);
    int n = recvfrom(c, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&server_addr, &addr_len);
    if (n < 0) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("Divisors from server: %s\n", buffer);

    close(c);
    return 0;
}