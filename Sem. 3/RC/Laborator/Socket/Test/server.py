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

import errno
import socket
import os
import random
import signal

def deservire_client(conn):

    udp_info = conn.recv(BUFFER_SIZE).decode()
    udp_ip, udp_port = udp_info.split()
    udp_port = int(udp_port)
    udp_port_client = udp_port + 1

    # udp_ip si udp_port reprezinta adresa serverului UDP
    if not 1 <= udp_port <= 65534:
        print("Port UDP invalid.", flush=True)
        return
    
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_socket:
            try:
                udp_socket.bind((udp_ip, udp_port))
            except OSError as exc:
                if exc.errno != errno.EADDRINUSE:
                    raise
                print(f"Portul UDP {udp_ip}:{udp_port} este deja ocupat.", flush=True)
                return

            # Trimitere mesaj client ca jocul a inceput
            udp_socket.sendto("Jocul a inceput".encode(), (udp_ip, udp_port_client))
            print(f"Mesaj trimis clientului UDP {udp_ip}:{udp_port_client} ca jocul a inceput.", flush=True)

            dim_info, _ = udp_socket.recvfrom(BUFFER_SIZE)
            text = dim_info.decode()

            if text == "STOP":
                print(f"Clientul a abandonat jocul {udp_ip}:{udp_port_client}.", flush=True)
                return

            dim = int(text)

            if dim < 4 or dim > 9:
                print("Dimensiune matrice invalida.", flush=True)
                return
            print(f"Dimensiune matrice primita de la client {udp_ip}:{udp_port_client}: {dim}", flush=True)

            # Initializare matrice joc cu dimensiunea primita
            matrice = [[0 for _ in range(dim)] for _ in range(dim)]
            print(f"Matrice joc pentru client {udp_ip}:{udp_port_client} initializata cu dimensiunea {dim}x{dim}", flush=True)

            # Plasare aleatorie a avioanelor in matrice
            numar_avioane = dim
            avioane_plasate = 0
            lista_pozitii = []
            while avioane_plasate < numar_avioane:
                linie = random.randint(0, dim - 1)
                coloana = random.randint(0, dim - 1)
                if matrice[linie][coloana] == 0:
                    matrice[linie][coloana] = 1
                    avioane_plasate += 1
                    lista_pozitii.append((linie, coloana))

            print(f"Avioanele plasate pentru client {udp_ip}:{udp_port_client}: {lista_pozitii}", flush=True)

            # Incepe jocul "Razboi" 
            numar_greseli = 0
            numar_avioane_ramase = numar_avioane
            while numar_avioane_ramase > 0 and numar_greseli < 5:

                coordonate_info, _ = udp_socket.recvfrom(BUFFER_SIZE)
                text = coordonate_info.decode()

                if text == "STOP":
                    print(f"Clientul a abandonat jocul {udp_ip}:{udp_port_client}.", flush=True)
                    return

                linie, coloana = map(int, text.split())

                # Verificam daca coordonatele sunt valide
                if linie < 0 or linie >= dim or coloana < 0 or coloana >= dim:
                    udp_socket.sendto("Coordonate invalide".encode(), (udp_ip, udp_port_client))
                    continue

                if matrice[linie][coloana] == 1:
                    matrice[linie][coloana] = -1
                    numar_avioane_ramase -= 1
                    message = "DA"
                else:
                    numar_greseli += 1
                    message = "NU"

                # Adaugam numarul de greseli si numarul de avioane ramase in mesaj doar daca nu se opreste jocul
                message += f", Numar greseli: {numar_greseli}, Numar avioane ramase: {numar_avioane_ramase}"

                if numar_avioane_ramase == 0:
                    message = "Ai castigat"
                    print(f"Client {udp_ip}:{udp_port_client} a castigat jocul.", flush=True)
                elif numar_greseli == 5:
                    message = "Ai pierdut"
                    print(f"Client {udp_ip}:{udp_port_client} a pierdut jocul.", flush=True)

                udp_socket.sendto(message.encode(), (udp_ip, udp_port_client))



TCP_IP = '127.0.0.1'
TCP_PORT = 12345
BUFFER_SIZE = 1024

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as tcp_socket:
    tcp_socket.bind((TCP_IP, TCP_PORT))
    tcp_socket.listen(5)

    signal.signal(signal.SIGCHLD, signal.SIG_IGN)

    while True:
        conn, addr = tcp_socket.accept()
        pid = os.fork()
        if pid == 0:
            tcp_socket.close()
            deservire_client(conn)
            conn.close()
            os._exit(0)
        else:
            conn.close()