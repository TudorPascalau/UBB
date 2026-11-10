# Se cere sa se simuleze jocul "avioane", prin comunicare atat TCP cat si UDP.
# Clientul ii va trimite serverului o adresa ip si un port udp, dupa care va fi incheiata comunicarea prin TCP.
# Ulterior, clientul va comunica cu serverul prin UDP, unde se va juca jocul "avioane":
# Serverul are un grid de 5*5, cu 5 avioane puse aleator pe acesta.
# Clientul va trimite incercari de locatie (de genul 2C) pentru a incerca sa gaseasca avioanele
# La fiecare incercare clientului ii va fi transmis daca a lovit un avion sau nu.
# Jocul se incheie atunci cand fiecare avion a fost gasit sau cand clientul trimite STOP.
# Serverul sa fie concurent prin fork() pentru a putea deservi mai multi clienti deodata.
# Pozitiile avioanelor sa fie generate aleator.
# La fiecare conexiune UDP, serverul va afisa pentru clientul deservit care sunt pozitiile avioanelor

import errno
import socket
import random
import os
from multiprocessing import Lock

tastatura = Lock()

random.seed(os.getpid())

def genereaza_avioane():
    avioane = set()
    while len(avioane) < 5:
        linie = random.randint(0, 4)
        coloana = random.randint(0, 4)
        avioane.add((linie, coloana))
    return avioane

def deservire_client(client_tcp_socket):
    # Primim informatiile UDP de la client prin TCP
    data = client_tcp_socket.recv(1024).decode().strip()
    client_udp_ip, client_udp_port = data.split(':')
    client_udp_port = int(client_udp_port)

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_socket:
        try:
            udp_socket.bind((client_udp_ip, client_udp_port))
        except OSError as exc:
            if exc.errno != errno.EADDRINUSE:
                raise
            print(f"Portul UDP {client_udp_ip}:{client_udp_port} este deja ocupat.", flush=True)
            return

        avioane = genereaza_avioane()
        with tastatura:
            print(f"Pozitiile avioanelor pentru clientul {client_udp_ip}:{client_udp_port} sunt: {avioane}")

        # Jocul "avioane" prin UDP
        while True:
            data, addr = udp_socket.recvfrom(1024)
            #print(f"UDP primit: {data!r}, lungime: {len(data)}", flush=True)
            message = data.decode().strip()
            if message.upper() == "STOP":
                break
            if len(message) != 2:
                udp_socket.sendto("Invalid input\n".encode(), addr)
                continue
            linie = int(message[0]) - 1
            coloana = ord(message[1].upper()) - ord('A')
            if (linie, coloana) in avioane:
                avioane.remove((linie, coloana))
                if not avioane:
                    udp_socket.sendto(b"All planes found\n", addr)
                    break
                udp_socket.sendto(b"Hit\n", addr)
            else:
                udp_socket.sendto(b"Miss\n", addr)
        

TCP_IP = '0.0.0.0'
TCP_PORT = 12345
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as tcp_socket:
    tcp_socket.bind((TCP_IP, TCP_PORT))
    tcp_socket.listen(5)
    while True:
        client_tcp_socket, addr = tcp_socket.accept()
        if os.fork() == 0:
            tcp_socket.close()
            deservire_client(client_tcp_socket)
            client_tcp_socket.close()
            os._exit(0)
        else:
            client_tcp_socket.close()