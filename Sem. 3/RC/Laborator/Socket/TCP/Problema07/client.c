#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    int c;
    struct sockaddr_in server;

    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c == -1) {
        perror("socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(5005);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(c, (struct sockaddr*)&server, sizeof(server)) == -1) {
        perror("connect");
        close(c);
        exit(1);
    }
    char message[1024];
    printf("Enter a message to send to the server: ");
    fgets(message, sizeof(message), stdin);
    send(c, message, strlen(message), 0);

    int subseq_length;
    printf("Enter subsequence length: ");
    scanf("%d", &subseq_length);
    subseq_length = htonl(subseq_length);
    send(c, &subseq_length, 4, 0);

    int start_index;
    printf("Enter start index: ");
    scanf("%d", &start_index);
    start_index = htonl(start_index);
    send(c, &start_index, 4, 0);

    char subseq[1024];
    int n = recv(c, subseq, sizeof(subseq) - 1, 0);
    if (n > 0) {
        subseq[n] = '\0';
        printf("Received subsequence from server: %s\n", subseq);
    }

    close(c);

    return 0;
}