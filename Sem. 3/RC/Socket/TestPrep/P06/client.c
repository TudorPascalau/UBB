/*
Se cere sa se simuleze jocul "avioane", prin comunicare atat TCP cat si UDP.
Clientul ii va trimite serverului o adresa ip si un port udp, dupa care va fi incheiata comunicarea prin TCP.
Ulterior, clientul va comunica cu serverul prin UDP, unde se va juca jocul "avioane":
Serverul are un grid de 5*5, cu 5 avioane puse aleator pe acesta.
Clientul va trimite incercari de locatie (de genul 2C) pentru a incerca sa gaseasca avioanele
La fiecare incercare clientului ii va fi transmis daca a lovit un avion sau nu.
Jocul se incheie atunci cand fiecare avion a fost gasit sau cand clientul trimite STOP.
Serverul sa fie concurent prin fork() pentru a putea deservi mai multi clienti deodata.
Pozitiile avioanelor sa fie generate aleator
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    // Citim de la tastatura adresa IP si portul UDP al serverului
    char server_ip[16];
    int server_udp_port;
    printf("Introduceti adresa IP a serverului: ");
    scanf("%15s", server_ip);
    printf("Introduceti portul UDP al serverului: ");
    scanf("%d", &server_udp_port);

    // Creem socket-ul UDP
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket < 0) {
        perror("Eroare la crearea socket-ului UDP");
        exit(1);
    }

    struct sockaddr_in server_udp_addr;
    memset(&server_udp_addr, 0, sizeof(server_udp_addr));
    server_udp_addr.sin_family = AF_INET;
    server_udp_addr.sin_port = htons(server_udp_port);
    if (inet_pton(AF_INET, server_ip, &server_udp_addr.sin_addr) <= 0) {
        perror("Adresa IP invalida");
        exit(1);
    }

    // Conectare la server TCP
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket < 0) {
        perror("Eroare la crearea socket-ului TCP");
        exit(1);
    }
    struct sockaddr_in server_tcp_addr;
    memset(&server_tcp_addr, 0, sizeof(server_tcp_addr));
    server_tcp_addr.sin_family = AF_INET;
    server_tcp_addr.sin_port = htons(12345); // Portul TCP al serverului
    if (inet_pton(AF_INET, server_ip, &server_tcp_addr.sin_addr) <= 0) {
        perror("Adresa IP invalida");
        exit(1);
    }

    if (connect(tcp_socket, (struct sockaddr*)&server_tcp_addr, sizeof(server_tcp_addr)) < 0) {
        perror("Eroare la conectarea la serverul TCP");
        exit(1);
    }

    // Trimitem adresa IP si portul UDP al clientului catre server prin TCP
    char udp_info[32];
    snprintf(udp_info, sizeof(udp_info), "%s:%d", server_ip, server_udp_port);
    if (send(tcp_socket, udp_info, strlen(udp_info), 0) < 0) {
        perror("Eroare la trimiterea informatiilor UDP catre server");
        exit(1);
    }

    // Inchidem socket-ul TCP dupa conectare
    close(tcp_socket);

    // Comunicam prin UDP
    char buffer[1024];
    while (1) {
        // Citim pozitia de la tastatura
        printf("Introduceti pozitia (ex: 2C): ");
        scanf("%s", buffer);
        if (sendto(udp_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&server_udp_addr, sizeof(server_udp_addr)) < 0) {
            perror("Eroare la trimiterea mesajului UDP");
            exit(1);
        }
        if (strcmp(buffer, "STOP") == 0) {
            break;
        }
        // Primim raspunsul de la server
        socklen_t server_udp_addr_len = sizeof(server_udp_addr);
        int recv_len = recvfrom(udp_socket, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&server_udp_addr, &server_udp_addr_len);
        if (recv_len < 0) {
            perror("Eroare la primirea mesajului UDP");
            exit(1);
        }
        
        buffer[recv_len] = '\0';
        printf("Raspuns server: %s", buffer);

        if (strcmp(buffer, "All planes found\n") == 0) {
            break;
        }
    }
    close(udp_socket);

    return 0;
}