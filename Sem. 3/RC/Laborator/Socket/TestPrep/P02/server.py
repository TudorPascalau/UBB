# Se doreste realizarea unei aplicatii client-server care simuleaza un joc de tip "fazan", desfasurat intre un server si unul sau mai multi clienti.
# Aplicatia trebuie sa utlizeze socketuri TCP si UDP pentru comunicare, iar serverul sa fie capabil sa gestioneze mai multi clienti simultan.
# Fiecare client se conecteaza la server prin TCP si ii transmite adresa IP si portul UDP pe care va asculta pentru joc.
# Dupa primirea acestor informatii, serverul inchide conexiunea TCP si initiaza comunicarea UDP cu clientul.
# Jocul de fazan se desfasoara exclusiv prin mesaje UDP. Serverul trimite un cuvant initial catre client.
# Clientul trebuie sa raspunda cu un cuvant care incepe cu ultimele doua litere ale cuvantului primit.
# Serverul citeste apoi un cuvant de la tastatura verifica daca acesta respecta regula jocului.
# Daca cuvantul introdus de server nu incepe cu ultimele doua litere ale cuvantului primit de la client, serverul va trimite automat mesajul "STOP"
#   si va incheia jocul cu acel client
# Serverul trebuie sa fie concurent, adica sa poata gestiona mai multi clienti simultan.
# Pentru acest lucru se va folosi mecanismul de forking, astfel incat fiecare client sa fie tratat intr-un proces separat.
# Aplicatia trebuie sa trateze corect cazurile de incheiere a jocului, erori de comunicare si validari de cuvinte.
# Clientul nu poate sa trimita STOP, doar serverul face verificari

import os
import signal
import socket

from multiprocessing import Lock

tastatura = Lock()

def cuvant_valid(cuvant, anterior):
    # Primele doua litere ale cuvantului anterior trebuie sa fie egale cu ultimele doua litere ale cuvantului curent
    if len(cuvant) < 2 or len(anterior) < 2:
        return False
    return cuvant[:2] == anterior[-2:]

def deservire_client(client_udp_ip, client_udp_port):
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.settimeout(120)

    # Citim de la tastatura primul cuvant pe care sa il trimitem clientului
    with tastatura:
        first_word = input(f"Introduceti primul cuvant pentru {client_udp_ip}:{client_udp_port}: ")
    udp_socket.sendto(first_word.encode(), (client_udp_ip, client_udp_port))

    # Primim raspunsul de la client
    response, _ = udp_socket.recvfrom(1024)
    print(f"Raspuns de la {client_udp_ip}:{client_udp_port}: {response.decode()}")

    # Verificam sa fie un cuvant valid
    if not cuvant_valid(response.decode(), first_word):
        udp_socket.sendto("STOP".encode(), (client_udp_ip, client_udp_port))
        udp_socket.close()
        return
    
    while True:
        # Citim cuvantul de la tastatura pentru a-l trimite clientului
        with tastatura:
            word = input(f"Introduceti cuvantul pentru {client_udp_ip}:{client_udp_port}: ")
        if not cuvant_valid(word, response.decode()):
            udp_socket.sendto("STOP".encode(), (client_udp_ip, client_udp_port))
            break

        # Trimitem cuvantul catre client
        udp_socket.sendto(word.encode(), (client_udp_ip, client_udp_port))
        # Primim raspunsul de la client
        response, _ = udp_socket.recvfrom(1024)
        print(f"Raspuns de la {client_udp_ip}:{client_udp_port}: {response.decode()}")

        # Verificam sa fie un cuvant valid
        if not cuvant_valid(response.decode(), word):
            udp_socket.sendto("STOP".encode(), (client_udp_ip, client_udp_port))
            break

    
    udp_socket.close()



TCP_IP = "0.0.0.0"
TCP_PORT = 12345

tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp_socket.bind((TCP_IP, TCP_PORT))
tcp_socket.listen(5)

signal.signal(signal.SIGCHLD, signal.SIG_IGN)

while True:
    client_tcp_socket, client_address = tcp_socket.accept()

    if os.fork() == 0:
        try:
            with client_tcp_socket:
                data = client_tcp_socket.recv(1024).decode()
                client_udp_ip, port_text = data.split()
                client_udp_port = int(port_text)
                if not 1 <= client_udp_port <= 65535:
                    raise ValueError("Port UDP invalid")

            deservire_client(client_udp_ip, client_udp_port)
        except (OSError, ValueError, EOFError) as eroare:
            print(f"{client_address}: sesiune încheiată ({eroare})", flush=True)
            os._exit(1)

        os._exit(0)
        
    else:
        client_tcp_socket.close()