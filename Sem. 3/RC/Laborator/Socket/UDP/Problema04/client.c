// Un client trimite unui server un sir de lungime cel mult 100 de caractere. Serverul va returna clientului acest sir oglindit (caracterele sirului in ordine inversa).
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

    char message[101];
    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character if present
    sendto(c, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    char buffer[101];
    socklen_t addr_len = sizeof(server_addr);
    int n = recvfrom(c, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&server_addr, &addr_len);
    if (n < 0) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("Reversed message from server: %s\n", buffer);

    close(c);
    return 0;
}