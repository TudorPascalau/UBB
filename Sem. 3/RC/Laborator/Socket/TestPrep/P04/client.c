#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    // Citim adresa IP si portul UDP de la utilizator
    char udp_ip[16];
    int udp_port;

    printf("Introduceti adresa IP UDP: ");
    if (scanf("%15s", udp_ip) != 1)
        return 1;

    printf("Introduceti portul UDP: ");
    if (scanf("%d", &udp_port) != 1 || udp_port < 1 || udp_port > 65535)
        return 1;

    // Setam adresa UDP a clientului
    struct sockaddr_in udp_addr = {0};
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(udp_port);
    if (inet_pton(AF_INET, udp_ip, &udp_addr.sin_addr) != 1) {
        fprintf(stderr, "Adresa IP UDP invalida.\n");
        return 1;
    }

    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket < 0) {
        perror("socket UDP");
        return 1;
    }

    if (bind(udp_socket, (struct sockaddr *)&udp_addr, sizeof(udp_addr)) < 0) {
        perror("bind UDP");
        close(udp_socket);
        return 1;
    }

    // Ne conectam la serverul TCP
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket < 0) {
        perror("socket TCP");
        close(udp_socket);
        return 1;
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5005);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(tcp_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(tcp_socket);
        close(udp_socket);
        return 1;
    }
    // Trimitem adresa IP si portul UDP catre serverul TCP
    char buffer[1024];
    int lungime = snprintf(buffer, sizeof(buffer), "%s %d", udp_ip, udp_port);
    int trimis = 0;
    while (trimis < lungime) {
        ssize_t n = send(tcp_socket, buffer + trimis, lungime - trimis, 0);
        if (n <= 0) {
            perror("send");
            close(tcp_socket);
            close(udp_socket);
            return 1;
        }
        trimis += n;
    }
    close(tcp_socket);

    // Asteptam si procesam mesajele UDP de la server
    while (1) {
        // Primim mesajele UDP de la server
        struct sockaddr_in client_udp_addr;
        socklen_t addr_len = sizeof(client_udp_addr);
        ssize_t n = recvfrom(udp_socket, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client_udp_addr, &addr_len);
        if (n < 0) {
            perror("recvfrom");
            close(udp_socket);
            return 1;
        }

        // Verificam daca serverul UDP a trimis STOP
        buffer[n] = '\0';
        if (strcmp(buffer, "STOP") == 0) {
            puts("Serverul UDP a trimis STOP. Jocul s-a incheiat.");
            break;
        }

        // Afisam cuvantul primit de la serverul UDP si cerem urmatorul cuvant de la utilizator
        printf("Cuvant primit de la serverul UDP: %s\n", buffer);
        printf("Introduceti urmatorul cuvant: ");
        if (scanf("%1023s", buffer) != 1)
            break;

        if (sendto(udp_socket, buffer, strlen(buffer), 0,
                   (struct sockaddr *)&client_udp_addr, addr_len) < 0) {
            perror("sendto");
            close(udp_socket);
            return 1;
        }
    }

    close(udp_socket);
    return 0;
}