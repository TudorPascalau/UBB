/*
# Sa se simuleze jocul "turnurile din Hanoi" prin comunicare atat TCP cat si UDP.
# Initial, clientul va comunica cu serverul prin TCP.
# Clientul va trimite serverului o adresa IP si un port UDP, dupa care va fi incheiata comunicarea prin TCP.
# Ulterior, clientul va comunica cu serverul prin UDP pentru a juca jocul "turnurile din Hanoi".
# Serverul va tine starea jocului, folosind 3 tije.
# Clientul va trimite numarul de discuri pentru jocul "turnurile din Hanoi".
# Clientul va trimite mutarile prin UDP, iar serverul va raspunde cu starea tijelor dupa fiecare mutare.
# Tija 1: tija sursa
# Tija 2: tija auxiliara
# Tija 3: tija tinta
# Jocul se incheie atunci cand toate discurile au fost mutate corect pe tija tinta sau cand clientul trimite STOP.
# Mutarile se vor trimite sub forma "sursa destinatie", de exemplu "1 3" pentru a muta discul de pe tija 1 pe tija 3.
# Serverul va putea deservi mai multi clienti deodata folosind fork() sau un mecanism similar.
*/

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

    // Initializare buffer si lungime adresa server UDP
    char buffer[1024];
    socklen_t udp_server_addr_len = sizeof(udp_server_addr);

    // Citire numar discuri sub forma de string
    char num_discuri_str[16];
    printf("Introduceti numarul de discuri: ");
    if (scanf("%15s", num_discuri_str) != 1) {
        return EXIT_FAILURE;
    }

    if (sendto(udp_socket, num_discuri_str, strlen(num_discuri_str), 0,
               (struct sockaddr*)&udp_server_addr, sizeof(udp_server_addr)) < 0) {
        perror("Eroare la trimiterea numarului de discuri catre serverul UDP");
        exit(EXIT_FAILURE);
    }

    // Jocul "turnurile din Hanoi" prin UDP
    while(1) {
        char sursa[16], destinatie[16];
        char move[32];
        printf("Introduceti mutarea (sursa destinatie) sau STOP pentru a opri: ");
        if (scanf("%15s", sursa) != 1) {
            return EXIT_FAILURE;
        }

        if (strcmp(sursa, "STOP") == 0) {
            snprintf(move, sizeof(move), "%s", sursa);
        } 
        else {
            if (scanf("%15s", destinatie) != 1) {
                return EXIT_FAILURE;
            }
            snprintf(move, sizeof(move), "%s %s", sursa, destinatie);
        }

        if (sendto(udp_socket, move, strlen(move), 0,
                   (struct sockaddr*)&udp_server_addr, sizeof(udp_server_addr)) < 0) {
            perror("Eroare la trimiterea mutarii catre serverul UDP");
            exit(EXIT_FAILURE);
        }

        if (strcmp(move, "STOP") == 0) {
            break;
        }

        int n = recvfrom(udp_socket, buffer, sizeof(buffer) - 1, 0,
                         (struct sockaddr*)&udp_server_addr, &udp_server_addr_len);
        if (n < 0) {
            perror("Eroare la primirea raspunsului de la serverul UDP");
            exit(EXIT_FAILURE);
        }
        buffer[n] = '\0';
        printf("Raspuns server UDP: %s\n", buffer);

        if (strncmp(buffer, "Joc incheiat!", 13) == 0) {
            close(udp_socket);
            break;
        }
    }

    return 0;
}