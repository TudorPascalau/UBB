
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {

    // Citire IP si port UDP
    char udp_ip[16];
    int udp_port;
    printf("Introduceti IP-ul clientului UDP: ");
    scanf("%15s", udp_ip);
    printf("Introduceti portul clientului UDP: ");
    scanf("%d", &udp_port);

    if (udp_port < 1 || udp_port > 65534) {
        fprintf(stderr, "Port invalid.\n");
        exit(EXIT_FAILURE);
    }

    // Creare socket UDP
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket < 0) {
        perror("Eroare la crearea socket-ului UDP");
        exit(EXIT_FAILURE);
    }

    // Adresa locala a clientului UDP
    struct sockaddr_in udp_client_addr;
    memset(&udp_client_addr, 0, sizeof(udp_client_addr));
    udp_client_addr.sin_family = AF_INET;
    udp_client_addr.sin_port = htons(udp_port);

    if (inet_pton(AF_INET, udp_ip, &udp_client_addr.sin_addr) <= 0) {
        fprintf(stderr, "IP client UDP invalid.\n");
        exit(EXIT_FAILURE);
    }

    if (bind(udp_socket, (struct sockaddr*)&udp_client_addr,
            sizeof(udp_client_addr)) < 0) {
        perror("Eroare la bind client UDP");
        exit(EXIT_FAILURE);
    }

    // Serverul UDP foloseste portul clientului + 1
    struct sockaddr_in udp_server_addr;
    memset(&udp_server_addr, 0, sizeof(udp_server_addr));
    udp_server_addr.sin_family = AF_INET;
    udp_server_addr.sin_port = htons(udp_port + 1);

    if (inet_pton(AF_INET, "127.0.0.1", &udp_server_addr.sin_addr) <= 0) {
        fprintf(stderr, "IP server UDP invalid.\n");
        exit(EXIT_FAILURE);
    }

    // Conectare la serverul TCP
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket < 0) {
        perror("Eroare la crearea socket-ului TCP");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in tcp_server_addr;
    memset(&tcp_server_addr, 0, sizeof(tcp_server_addr));
    tcp_server_addr.sin_family = AF_INET;
    tcp_server_addr.sin_port = htons(12345); // Portul serverului TCP
    if (inet_pton(AF_INET, "127.0.0.1", &tcp_server_addr.sin_addr) <= 0) {
        perror("Eroare la conversia IP-ului TCP");
        exit(EXIT_FAILURE);
    }

    if (connect(tcp_socket, (struct sockaddr*)&tcp_server_addr, sizeof(tcp_server_addr)) < 0) {
        perror("Eroare la conectarea la serverul TCP");
        exit(EXIT_FAILURE);
    }

    // Trimitere IP si port UDP catre serverul TCP
    char udp_info[32];
    snprintf(udp_info, sizeof(udp_info), "%s %d", udp_ip, udp_port);
    if (send(tcp_socket, udp_info, strlen(udp_info), 0) < 0) {
        perror("Eroare la trimiterea informatiilor UDP catre serverul TCP");
        exit(EXIT_FAILURE);
    }
    
    close(tcp_socket); // Inchidere socket TCP dupa trimiterea informatiilor UDP

    // Incepe jocul "Ghicit cuvant" prin UDP
    while(1) {
        char guess[32];
        printf("Introduceti cuvantul ghicit sau STOP pentru a opri: ");
        if (scanf("%31s", guess) != 1) {
            return EXIT_FAILURE;
        }

        if (sendto(udp_socket, guess, strlen(guess), 0,
                   (struct sockaddr*)&udp_server_addr, sizeof(udp_server_addr)) < 0) {
            perror("Eroare la trimiterea cuvantului catre serverul UDP");
            exit(EXIT_FAILURE);
        }

        if (strcmp(guess, "STOP") == 0) {
            break;
        }

        char buffer[1024];
        socklen_t udp_server_addr_len = sizeof(udp_server_addr);
        int n = recvfrom(udp_socket, buffer, sizeof(buffer) - 1, 0,
                         (struct sockaddr*)&udp_server_addr, &udp_server_addr_len);
        if (n < 0) {
            perror("Eroare la primirea raspunsului de la serverul UDP");
            exit(EXIT_FAILURE);
        }
        buffer[n] = '\0';
        printf("Raspuns server UDP: %s\n", buffer);

        if (strncmp(buffer, "Felicitari! Ati ghicit cuvantul!", 34) == 0) {
            close(udp_socket);
            break;
        }
    }

    return 0;
}