/*
# Se doreste crearea unei aplicatii de tip Clinet-Server care simuleaza un joc de tip RAZBOI
# Aplicatia treubie sa utilieze socketuri TCP si UDP pentru comunicare, iar serverul sa fie capabil sa gestioneze mai multi clienti simultan
# La pornire serverul asculta pe un port TCP prestabilit
# Fiecare client se conecteaza prin TCP la server si comunica IP si PORT UDP pe care serverul trebuie sa deruleze jocul

# Clientul trimite serverului un numar intreg n cuprins intre 4 si 9
# Serverul primeste numarul si genereaza o matrice de dimensiune n * n pe care o initializeaza cu 0
# Dupa aceea serverul genereaza n pozitii din matrice (de tipul (linie, coloana)) pe care le marcheaza cu 1 (pozitiile avioanelor)
# Serverul trimite clientului un mesaj prin care il anunta ca jocul a inceput
# Clientul trimite serverului pozitia pe care crede ca se afla un avion.
# Serverul ii raspunde clientului un mesaj ce contine:
# - "DA" (avionul a fost lovit) sau "NU" (avionul nu a fost lovit)
# - numarul de greseli
# - numarul de avioane ramase neatinse
# Jocul continua pana cand clientul loveste toate avioanele sau face 5 greseli (serverul contorizeaza greselile)
# La finalul jocului serverul trimite clientului concluzia jocului (castigat sau pierdut)
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

void abandoneaza_jocul(int udp_socket, const struct sockaddr_in *server_addr) {
    if (sendto(udp_socket, "STOP", 4, 0, (const struct sockaddr *)server_addr, sizeof(*server_addr)) < 0) {
        perror("Eroare la trimiterea mesajului STOP");
    }

    close(udp_socket);
    exit(EXIT_FAILURE);
}

int main() {

    char udp_ip[16];
    int udp_port;
    printf("Introduceti IP-ul serverului UDP: ");
    if (scanf("%15s", udp_ip) != 1) {
        fprintf(stderr, "Eroare la citirea IP-ului UDP.\n");
        exit(EXIT_FAILURE);
    }
    printf("Introduceti portul serverului UDP: ");
    if (scanf("%d", &udp_port) != 1) {
        fprintf(stderr, "Eroare la citirea portului UDP.\n");
        exit(EXIT_FAILURE);
    }

    if (udp_port < 1 || udp_port > 65534) {
        fprintf(stderr, "Port invalid.\n");
        exit(EXIT_FAILURE);
    }

    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket < 0) {
        perror("Eroare la crearea socket-ului UDP");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in udp_client_addr;
    memset(&udp_client_addr, 0, sizeof(udp_client_addr));
    udp_client_addr.sin_family = AF_INET;
    udp_client_addr.sin_port = htons(udp_port + 1);

    if (inet_pton(AF_INET, udp_ip, &udp_client_addr.sin_addr) <= 0) {
        fprintf(stderr, "IP client UDP invalid.\n");
        exit(EXIT_FAILURE);
    }

    if (bind(udp_socket, (struct sockaddr*)&udp_client_addr,
            sizeof(udp_client_addr)) < 0) {
        perror("Eroare la bind client UDP");
        exit(EXIT_FAILURE);
    }


    struct sockaddr_in udp_server_addr;
    memset(&udp_server_addr, 0, sizeof(udp_server_addr));
    udp_server_addr.sin_family = AF_INET;
    udp_server_addr.sin_port = htons(udp_port);
    if (inet_pton(AF_INET, udp_ip, &udp_server_addr.sin_addr) <= 0) {
        fprintf(stderr, "IP server UDP invalid.\n");
        exit(EXIT_FAILURE);
    }


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

    char udp_info[32];
    snprintf(udp_info, sizeof(udp_info), "%s %d", udp_ip, udp_port);
    if (send(tcp_socket, udp_info, strlen(udp_info), 0) < 0) {
        perror("Eroare la trimiterea informatiilor UDP catre serverul TCP");
        exit(EXIT_FAILURE);
    }
    
    close(tcp_socket);

    // Primire mesaj de la serverul UDP ca jocul a inceput
    char buffer[1024];
    socklen_t udp_server_addr_len = sizeof(udp_server_addr);
    int n = recvfrom(udp_socket, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr*)&udp_server_addr, &udp_server_addr_len);
    if (n < 0) {
        perror("Eroare la primirea mesajului de la serverul UDP");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("Mesaj de la server UDP: %s\n", buffer);

    // Verificare daca mesajul primit este cel asteptat
    if (strcmp(buffer, "Jocul a inceput") != 0) {
        fprintf(stderr, "Mesaj UDP neasteptat: %s\n", buffer);
        exit(EXIT_FAILURE);
    }

    int dim;
    printf("Introduceti dimensiunea matricei (4-9): ");
    if (scanf("%d", &dim) != 1 || dim < 4 || dim > 9) {
        fprintf(stderr, "Dimensiune invalida.\n");
        abandoneaza_jocul(udp_socket, &udp_server_addr);
        exit(EXIT_FAILURE);
    }

    // Trimitere dimensiune matrice catre serverul UDP
    char dim_info[32];
    snprintf(dim_info, sizeof(dim_info), "%d", dim);
    if (sendto(udp_socket, dim_info, strlen(dim_info), 0,
               (struct sockaddr*)&udp_server_addr, sizeof(udp_server_addr)) < 0) {
        perror("Eroare la trimiterea dimensiunii matricei catre serverul UDP");
        abandoneaza_jocul(udp_socket, &udp_server_addr);
        exit(EXIT_FAILURE);
    }


    // Incepe jocul "Razboi" prin UDP
    while(1) {
        int linie, coloana;
        printf("Introduceti coordonatele (linie coloana): ");
        if (scanf("%d %d", &linie, &coloana) != 2) {
            fprintf(stderr, "Date invalide.\n");
            continue;
        }

        // Trimitere coordonate catre serverul UDP
        char coordonate[32];
        snprintf(coordonate, sizeof(coordonate), "%d %d", linie, coloana);
        if (sendto(udp_socket, coordonate, strlen(coordonate), 0,
                   (struct sockaddr*)&udp_server_addr, sizeof(udp_server_addr)) < 0) {
            perror("Eroare la trimiterea coordonatelor catre serverul UDP");
            abandoneaza_jocul(udp_socket, &udp_server_addr);
            exit(EXIT_FAILURE);
        }

        // Primire raspuns de la serverul UDP
        n = recvfrom(udp_socket, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr*)&udp_server_addr, &udp_server_addr_len);
        if (n < 0) {
            perror("Eroare la primirea raspunsului de la serverul UDP");
            abandoneaza_jocul(udp_socket, &udp_server_addr);
            exit(EXIT_FAILURE);
        }
        buffer[n] = '\0';
        printf("Raspuns de la server UDP: %s\n", buffer);

        if (strcmp(buffer, "Ai castigat") == 0 || strcmp(buffer, "Ai pierdut") == 0) {
            break;
        }

        if (strncmp(buffer, "Coordonate invalide", 18) == 0) {
            fprintf(stderr, "Coordonate invalide. Incercati din nou.\n");
        }
    }

    close(udp_socket);

    return 0;
}