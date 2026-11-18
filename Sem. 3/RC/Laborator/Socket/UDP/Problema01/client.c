// Un client trimite unui server doua numere. Serverul va returna clientului suma celor doua numere.
// Se comunica prin UDP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

int main() {
    int s;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("socket");
        return 1;
    }
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2020); // portul serverului
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int num1, num2;
    printf("Introduceti primul numar: ");
    scanf("%d", &num1);
    num1 = htonl(num1);
    sendto(s, &num1, sizeof(num1), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("Introduceti al doilea numar: ");
    scanf("%d", &num2);
    num2 = htonl(num2);
    sendto(s, &num2, sizeof(num2), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    int sum;
    socklen_t addr_len = sizeof(server_addr);
    recvfrom(s, &sum, sizeof(sum), 0, (struct sockaddr*)&server_addr, &addr_len);
    printf("Suma: %d\n", ntohl(sum));

    close(s);
    return 0;
}