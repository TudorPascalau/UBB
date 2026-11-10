/*
# Se cere realizarea unei aplicații client–server care simulează jocul „fazan” între un server TCP și unul sau mai mulți clienți TCP. 
# Aplicația folosește TCP pentru inițializarea sesiunilor și UDP pentru desfășurarea jocului.
# Fiecare client TCP deschide un socket UDP pe care va asculta, se conectează la serverul TCP și îi transmite adresa IP și portul acelui socket. 
# După primirea acestor informații, serverul închide conexiunea TCP cu clientul respectiv.
# După etapa TCP, rolurile se inversează. 
# Fostul client TCP devine server UDP și așteaptă datagrame pe portul comunicat. 
# Fostul server TCP devine client UDP și inițiază jocul trimițând un cuvânt la adresa și portul primite.
# Serverul UDP răspunde cu un cuvânt care începe cu ultimele două litere ale cuvântului primit. 
# Clientul UDP citește apoi un cuvânt de la tastatură și verifică dacă acesta începe cu ultimele două litere ale răspunsului. 
# Dacă regula este respectată, clientul UDP trimite cuvântul și jocul continuă. 
# În caz contrar, clientul UDP trimite automat mesajul STOP și încheie sesiunea respectivă. 
# La primirea mesajului STOP, serverul UDP încheie și el sesiunea.
# Serverul TCP trebuie să accepte mai mulți clienți simultan, folosind fork(). 
# Pentru fiecare conexiune acceptată, un proces copil gestionează schimbul inițial prin TCP și continuă jocul în rolul de client UDP. 
# Procesul părinte rămâne disponibil pentru a accepta noi conexiuni TCP.
# Toate mesajele jocului, inclusiv STOP, sunt transmise exclusiv prin UDP. 
# Aplicația trebuie să valideze cuvintele, să trateze erorile de comunicare și să elibereze resursele la încheierea fiecărei sesiuni.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

static sem_t *tastatura;

int validare_cuvant(const char *cuvant, const char *anterior) {
    size_t lungime = strlen(anterior);
    if (lungime < 2 || strlen(cuvant) < 2)
        return 0;

    return strncmp(cuvant, anterior + lungime - 2, 2) == 0;
}

void deservire_client(int tcp_client_socket, struct sockaddr_in client_addr) {
    // Preluare adresa IP si port UDP de la clientul TCP
    char buffer[256];
    int bytes_received = recv(tcp_client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0) {
        perror("Recv failed");
        return;
    }
    buffer[bytes_received] = '\0';
    char udp_ip[128];
    int udp_port;
    sscanf(buffer, "%s %d", udp_ip, &udp_port);
    printf("Client UDP: %s:%d\n", udp_ip, udp_port);

    // Inchidere conexiune TCP cu clientul
    close(tcp_client_socket);

    // Creare socket UDP pentru a comunica cu clientul UDP
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket < 0) {
        perror("UDP socket creation failed");
        return;
    }

    struct sockaddr_in udp_client_addr = {0};
    udp_client_addr.sin_family = AF_INET;
    udp_client_addr.sin_port = htons(udp_port);
    udp_client_addr.sin_addr.s_addr = inet_addr(udp_ip);

    // Citim primul cuvant ca si client UDP
    sem_wait(tastatura); // Blocare semafor pentru citirea din terminal
    printf("Introduceti primul cuvant pentru %s:%d: ", udp_ip, udp_port);
    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Eliminare newline
    sem_post(tastatura); // Deblocare semafor

    // Trimitere cuvant catre server UDP
    if (sendto(udp_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&udp_client_addr, sizeof(udp_client_addr)) == -1) {
        perror("sendto");
        close(udp_socket);
        return;
    }
    // Incepe jocul cu serverul UDP (noi suntem client)

    while (1) {
            // Asteptam raspuns de la serverul UDP
            char raspuns[256];
            bytes_received = recvfrom(udp_socket, raspuns, sizeof(raspuns) - 1, 0, NULL, NULL);
            if (bytes_received < 0) {
                perror("Recvfrom failed");
                close(udp_socket);
                return;
            }
            raspuns[bytes_received] = '\0';
            printf("Cuvant primit de la server UDP: %s\n", raspuns);

            // Validare cuvant primit
            if (!validare_cuvant(raspuns, buffer)) {
                printf("Cuvantul primit nu este valid.\n");
                // Daca cuvantul este invalid trimitem STOP
                sendto(udp_socket, "STOP", 4, 0, (struct sockaddr*)&udp_client_addr, sizeof(udp_client_addr));
                close(udp_socket);
                return;
            }

            // Citim urmatorul cuvant de la clientul UDP
            sem_wait(tastatura); // Blocare semafor pentru citirea din terminal
            printf("Introduceti urmatorul cuvant pentru %s:%d: ", udp_ip, udp_port);
            fflush(stdout);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // Eliminare newline
            sem_post(tastatura); // Deblocare semafor

            if(!validare_cuvant(buffer, raspuns)) {
                printf("Cuvantul introdus nu respecta regula.\n");
                sendto(udp_socket, "STOP", 4, 0, (struct sockaddr*)&udp_client_addr, sizeof(udp_client_addr));
                close(udp_socket);
                return;
            }

            // Trimitere cuvant catre server UDP
            sendto(udp_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&udp_client_addr, sizeof(udp_client_addr));
    }
    
    
}

int main() {

    // Initializare semafor pentru protejarea citirii din terminal
    tastatura = sem_open("/tastatura", O_CREAT, 0644, 1);
    if (tastatura == SEM_FAILED) {
        perror("Semafor creation failed");
        exit(EXIT_FAILURE);
    }
    sem_unlink("/tastatura"); // Asigurare ca semaforul este eliminat la terminarea programului

    // Creare socket TCP 
    int tcp_server_socket, tcp_client_socket;
    struct sockaddr_in server_addr = {0}, client_addr = {0};
    socklen_t client_len = sizeof(client_addr);

    tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(5005);

    if (bind(tcp_server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(tcp_server_socket);
        exit(EXIT_FAILURE);
    }

    listen(tcp_server_socket, 5);

    // Acceptare conexiuni TCP
    while (1) {
        tcp_client_socket = accept(tcp_server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (tcp_client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        if (fork() == 0) {
            close(tcp_server_socket);
            deservire_client(tcp_client_socket, client_addr);
            close(tcp_client_socket);
            exit(0);
        }
        close(tcp_client_socket);
        waitpid(-1, NULL, WNOHANG);
    }

    return 0;
}