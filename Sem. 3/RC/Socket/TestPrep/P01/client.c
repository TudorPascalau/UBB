// Clientul alege un port UDP liber pe calculatorul său, creează un socket UDP și îl leagă la portul ales. 
// Apoi se conectează prin TCP la server și îi transmite numărul portului.
// Serverul creează un socket UDP pentru sesiunea curentă și încearcă să îl lege la același număr de port, pe propria adresă IP. 
// Serverul confirmă prin TCP dacă portul este disponibil. Dacă portul este ocupat, clientul poate alege altul. 
// După confirmare, conexiunea TCP se închide.
// Clientul trimite la adresa IP a serverului, pe portul confirmat, o singură datagramă care conține numărul de elemente și șirul de cel mult 100 de numere întregi.
// Serverul calculează suma numerelor prime din șir și o trimite de pe același socket UDP la adresa IP a clientului, pe același număr de port. 
// Dacă șirul nu conține numere prime, serverul trimite 0. Clientul primește și afișează rezultatul.
// Serverul deservește clienții pe rând. După ce trimite rezultatul, închide socketul UDP al sesiunii și revine la accept() pentru a prelua următorul client.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    
    // Crearea socketului TCP și conectarea la server
    int tcp_socket;
    struct sockaddr_in server_addr = {0};

    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket < 0) {
        perror("Eroare la crearea socketului TCP");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);  // Portul TCP al serverului
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Adresa IP a serverului

    if (connect(tcp_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Eroare la conectarea la server");
        close(tcp_socket);
        exit(EXIT_FAILURE);
    }

    // Trimiterea numărului portului UDP către server prin TCP
    int udp_port = 54321;  // Exemplu de port UDP ales de client
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%d", udp_port);
    if (send(tcp_socket, buffer, strlen(buffer), 0) < 0) {
        perror("Eroare la trimiterea portului UDP către server");
        close(tcp_socket);
        exit(EXIT_FAILURE);
    }
    close(tcp_socket);  // Închide conexiunea TCP după trimiterea portului UDP

    // Crearea socketului UDP și trimiterea datagramei către server
    int udp_socket;
    struct sockaddr_in udp_server_addr = {0};

    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket < 0) {
        perror("Eroare la crearea socketului UDP");
        exit(EXIT_FAILURE);
    }

    udp_server_addr.sin_family = AF_INET;
    udp_server_addr.sin_port = htons(udp_port);  // Portul UDP confirmat de server
    udp_server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Adresa IP a serverului

    // Citirea numarului de elemente și a șirului de numere întregi de la utilizator sub forma de text
    char udp_buffer[1024];
    printf("Introduceti numarul de elemente si numerele intregi separate prin spatiu: ");
    fgets(udp_buffer, sizeof(udp_buffer), stdin);
    // Eliminarea caracterului newline de la sfarsitul sirului, daca exista
    size_t len = strlen(udp_buffer);
    if (len > 0 && udp_buffer[len - 1] == '\n') {
        udp_buffer[len - 1] = '\0';
    }

    if (sendto(udp_socket, udp_buffer, strlen(udp_buffer), 0, (struct sockaddr*)&udp_server_addr, sizeof(udp_server_addr)) < 0) {
        perror("Eroare la trimiterea datagramei UDP către server");
        close(udp_socket);
        exit(EXIT_FAILURE);
    }

    // Primirea rezultatului de la server
    char result_buffer[16];
    socklen_t addr_len = sizeof(udp_server_addr);
    if (recvfrom(udp_socket, result_buffer, sizeof(result_buffer) - 1, 0, (struct sockaddr*)&udp_server_addr, &addr_len) < 0) {
        perror("Eroare la primirea rezultatului de la server");
        close(udp_socket);
        exit(EXIT_FAILURE);
    }
    result_buffer[sizeof(result_buffer) - 1] = '\0';
    printf("Suma numerelor prime: %s\n", result_buffer);

    close(udp_socket);
    return 0;
}