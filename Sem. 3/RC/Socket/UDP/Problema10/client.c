// Un client trimite unui server un nume de calculator sub forma unui sir de caractere de lungime cel mult 100. 
// Serverul va returna clientului un numar reprezentat pe 4 octeti fara semn ce reprezinta adresa IP a calculatorului respectiv. 
// Clientul va afisa corespunzator adresa IP (in format zecimal cu “.”) sau un mesaj de eroare daca numele calculatorului nu poate fi translatat intr-o adresa IP.
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
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5005);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char hostname[100];
    printf("Enter hostname: ");
    fgets(hostname, sizeof(hostname), stdin);
    hostname[strcspn(hostname, "\n")] = 0; // Remove newline character if present

    if (sendto(sock, hostname, strlen(hostname), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }

    unsigned int ip_addr;
    socklen_t addr_len = sizeof(server_addr);
    if (recvfrom(sock, &ip_addr, sizeof(ip_addr), 0, (struct sockaddr*)&server_addr, &addr_len) < 0) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }
    printf("IP address: %s\n", inet_ntoa(*(struct in_addr*)&ip_addr));
    close(sock);
    return 0;
}
