/*
Se cere realizarea unei aplicatii client-server care simuleaza jocul „fazan”.
Programul C gestioneaza mai multe jocuri simultan, cate unul pentru fiecare
proces copil creat cu fork(). Fiecare copil deschide un socket UDP pe un port
distinct, se conecteaza la serverul TCP corespunzator si ii transmite IP-ul
si portul UDP. Apoi inchide conexiunea TCP si devine server UDP.

Fostul server TCP devine client UDP si trimite primul cuvant. Serverul UDP
citeste un raspuns de la tastatura si il trimite clientului UDP. Fiecare
cuvant trebuie sa inceapa cu ultimele doua litere ale cuvantului anterior.
Clientul UDP verifica atat raspunsul primit, cat si urmatorul cuvant citit
de la tastatura. La prima abatere trimite STOP si incheie jocul.
Serverul UDP incheie sesiunea cand primeste STOP.

Serverele TCP sunt secventiale si citesc IP-ul si portul local de la tastatura.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

static sem_t *tastatura;

struct joc {
    char tcp_ip[16];
    int tcp_port;
    char udp_ip[16];
    int udp_port;
};

void joaca(struct joc joc) {
    struct sockaddr_in udp_addr = {0};
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(joc.udp_port);
    udp_addr.sin_addr.s_addr = inet_addr(joc.udp_ip);

    int udp = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp < 0) {
        perror("socket UDP");
        return;
    }

    if (bind(udp, (struct sockaddr *)&udp_addr, sizeof(udp_addr)) < 0) {
        perror("bind UDP");
        close(udp);
        return;
    }

    struct sockaddr_in tcp_addr = {0};
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(joc.tcp_port);
    tcp_addr.sin_addr.s_addr = inet_addr(joc.tcp_ip);

    int tcp = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp < 0) {
        perror("socket TCP");
        close(udp);
        return;
    }

    if (connect(tcp, (struct sockaddr *)&tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("connect");
        close(tcp);
        close(udp);
        return;
    }

    char buffer[1024];
    int lungime = snprintf(buffer, sizeof(buffer), "%s %d",
                           joc.udp_ip, joc.udp_port);
    int trimis = 0;
    while (trimis < lungime) {
        ssize_t n = send(tcp, buffer + trimis, lungime - trimis, 0);
        if (n <= 0) {
            perror("send");
            close(tcp);
            close(udp);
            return;
        }
        trimis += n;
    }
    close(tcp);

    while (1) {
        struct sockaddr_in client_udp;
        socklen_t lungime_adresa = sizeof(client_udp);
        ssize_t n = recvfrom(udp, buffer, sizeof(buffer) - 1, 0,
                             (struct sockaddr *)&client_udp, &lungime_adresa);
        if (n < 0) {
            perror("recvfrom");
            break;
        }

        buffer[n] = '\0';
        if (strcmp(buffer, "STOP") == 0) {
            printf("Jocul de pe portul UDP %d s-a incheiat.\n", joc.udp_port);
            break;
        }

        sem_wait(tastatura);
        printf("[%d] Cuvant primit: %s\n", joc.udp_port, buffer);
        printf("[%d] Introduceti raspunsul: ", joc.udp_port);
        fflush(stdout);
        int citit = scanf("%1023s", buffer);
        sem_post(tastatura);

        if (citit != 1)
            break;

        if (sendto(udp, buffer, strlen(buffer), 0,
                   (struct sockaddr *)&client_udp, lungime_adresa) < 0) {
            perror("sendto");
            break;
        }
    }

    close(udp);
}

int main(void) {
    int numar_jocuri;
    printf("Numarul de jocuri: ");
    if (scanf("%d", &numar_jocuri) != 1 || numar_jocuri < 1)
        return 1;

    struct joc jocuri[numar_jocuri];
    for (int i = 0; i < numar_jocuri; i++) {
        printf("Jocul %d - IP si port server TCP: ", i + 1);
        if (scanf("%15s %d", jocuri[i].tcp_ip, &jocuri[i].tcp_port) != 2 ||
            jocuri[i].tcp_port < 1 || jocuri[i].tcp_port > 65535)
            return 1;

        printf("Jocul %d - IP si port UDP local: ", i + 1);
        if (scanf("%15s %d", jocuri[i].udp_ip, &jocuri[i].udp_port) != 2 ||
            jocuri[i].udp_port < 1 || jocuri[i].udp_port > 65535)
            return 1;
    }

    tastatura = sem_open("/tastatura_fazan", O_CREAT, 0644, 1);
    if (tastatura == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }
    sem_unlink("/tastatura_fazan");

    fflush(stdout);
    for (int i = 0; i < numar_jocuri; i++) {
        int pid = fork();
        if (pid == 0) {
            joaca(jocuri[i]);
            return 0;
        }
        if (pid < 0)
            perror("fork");
    }

    while (waitpid(-1, NULL, 0) > 0) {
    }

    return 0;
}