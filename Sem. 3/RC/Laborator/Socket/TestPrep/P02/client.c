// Se doreste realizarea unei aplicatii client-server care simuleaza un joc de tip "fazan", desfasurat intre un server si unul sau mai multi clienti.
// Aplicatia trebuie sa utlizeze socketuri TCP si UDP pentru comunicare, iar serverul sa fie capabil sa gestioneze mai multi clienti simultan.
// Fiecare client se conecteaza la server prin TCP si ii transmite adresa IP si portul UDP pe care va asculta pentru joc.
// Dupa primirea acestor informatii, serverul inchide conexiunea TCP si initiaza comunicarea UDP cu clientul.
// Jocul de fazan se desfasoara exclusiv prin mesaje UDP. Serverul trimite un cuvant initial catre client.
// Clientul trebuie sa raspunda cu un cuvant care incepe cu ultimele doua litere ale cuvantului primit.
// Serverul citeste apoi un cuvant de la tastatura verifica daca acesta respecta regula jocului.
// Daca cuvantul introdus de server nu incepe cu ultimele doua litere ale cuvantului primit de la client, serverul va trimite automat mesajul "STOP"
//   si va incheia jocul cu acel client
// Serverul trebuie sa fie concurent, adica sa poata gestiona mai multi clienti simultan.
// Pentru acest lucru se va folosi mecanismul de forking, astfel incat fiecare client sa fie tratat intr-un proces separat.
// Aplicatia trebuie sa trateze corect cazurile de incheiere a jocului, erori de comunicare si validari de cuvinte.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {

    // Citim de la tastatura adresa IP si portul UDP pe care clientul va asculta pentru joc
    char udp_ip[16];
    int udp_port;
    printf("Introduceti adresa IP UDP: ");
    scanf("%15s", udp_ip);
    printf("Introduceti portul UDP: ");
    scanf("%d", &udp_port);
    
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s %d", udp_ip, udp_port);

    // Crearea socketului UDP pentru comunicarea cu serverul
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket < 0) {
        perror("Eroare la crearea socketului UDP");
        exit(1);
    }

    struct sockaddr_in udp_addr = {0};
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(udp_port);
    udp_addr.sin_addr.s_addr = inet_addr(udp_ip);

    if (bind(udp_socket, (struct sockaddr*)&udp_addr, sizeof(udp_addr)) < 0) {
        perror("Eroare la bind-ul socketului UDP");
        exit(1);
    }

    // Realizarea conexiunii initiale TCP catre server
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket < 0) {
        perror("Eroare la crearea socketului TCP");
        exit(1);
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(tcp_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Eroare la conectarea la server");
        exit(1);
    }

    // Trimitem informatiile UDP catre server prin TCP
    send(tcp_socket, buffer, strlen(buffer), 0);
    close(tcp_socket);


    // Asteptam primul cuvant de la server
    char recv_buffer[1024];
    struct sockaddr_in from_addr;
    socklen_t from_len = sizeof(from_addr);
    int recv_len = recvfrom(udp_socket, recv_buffer, sizeof(recv_buffer) - 1, 0,
                            (struct sockaddr*)&from_addr, &from_len);
    if (recv_len < 0) {
        perror("Eroare la primirea mesajului UDP");
        exit(1);
    }
    recv_buffer[recv_len] = '\0';
    printf("Cuvantul initial de la server: %s\n", recv_buffer);

    // Raspundem cu un cuvant care incepe cu ultimele doua litere ale cuvantului primit
    char send_buffer[1024];
    printf("Introduceti cuvantul care incepe cu ultimele doua litere ale cuvantului primit: ");
    scanf("%1023s", send_buffer);
    sendto(udp_socket, send_buffer, strlen(send_buffer), 0, (struct sockaddr*)&from_addr, from_len);

    // Incepem jocul pana cand serverul trimite "STOP"
    while (1) {
        recv_len = recvfrom(udp_socket, recv_buffer, sizeof(recv_buffer) - 1, 0, (struct sockaddr*)&from_addr, &from_len);
        if (recv_len < 0) {
            perror("Eroare la primirea mesajului UDP");
            exit(1);
        }

        recv_buffer[recv_len] = '\0';
        if (strcmp(recv_buffer, "STOP") == 0) {
            printf("Serverul a trimis STOP. Jocul s-a incheiat.\n");
            break;
        }

        printf("Cuvant de la server: %s\n", recv_buffer);

        printf("Introduceti cuvantul care incepe cu ultimele doua litere ale cuvantului primit: ");
        scanf("%1023s", send_buffer);
        sendto(udp_socket, send_buffer, strlen(send_buffer), 0, (struct sockaddr*)&from_addr, from_len);
    }

    close(udp_socket);

    return 0;
}