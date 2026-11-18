#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int c;
    struct sockaddr_in server_addr = {0};

    c = socket(AF_INET, SOCK_DGRAM, 0);
    if (c < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5005);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char message[101];
    printf("Enter a string: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;  // Remove trailing newline

    char letter;
    printf("Enter a character: ");
    scanf(" %c", &letter);
    getchar();  // Consume the newline character after the character input

    // sendto(c, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    sendto(c, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    // send the character separately
    sendto(c, &letter, sizeof(letter), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    char buffer[1024];
    socklen_t addr_len = sizeof(server_addr);
    int n = recvfrom(c, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&server_addr, &addr_len);
    if (n < 0) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("Positions: %s\n", buffer);

    close(c);
    return 0;
}