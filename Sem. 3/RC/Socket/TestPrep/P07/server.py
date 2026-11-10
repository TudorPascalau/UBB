# Sa se simuleze jocul "turnurile din Hanoi" prin comunicare atat TCP cat si UDP.
# Initial, clientul va comunica cu serverul prin TCP.
# Clientul va trimite serverului o adresa IP si un port UDP, dupa care va fi incheiata comunicarea prin TCP.
# Ulterior, clientul va comunica cu serverul prin UDP pentru a juca jocul "turnurile din Hanoi".
# Serverul va tine starea jocului, folosind 3 tije.
# Clientul va trimite numarul de discuri pentru jocul "turnurile din Hanoi".
# Clientul va trimite mutarile prin UDP, iar serverul va raspunde cu starea tijelor dupa fiecare mutare.
# Tija 1: tija sursa
# Tija 2: tija auxiliara
# Tija 3: tija tinta
# Jocul se incheie atunci cand toate discurile au fost mutate corect pe tija tinta sau cand clientul trimite STOP.
# Mutarile se vor trimite sub forma "sursa destinatie", de exemplu "1 3" pentru a muta discul de pe tija 1 pe tija 3.
# Serverul va putea deservi mai multi clienti deodata folosind fork() sau un mecanism similar.

import errno
import socket
import os

def deservire_client(conn):

    # Citire IP si port UDP de la client
    udp_info = conn.recv(BUFFER_SIZE).decode()
    udp_ip, udp_port = udp_info.split()
    udp_port = int(udp_port)

    # Conectare la serverul UDP
    udp_server_addr = (udp_ip, udp_port)
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_socket:
            try:
                udp_socket.bind((udp_ip, udp_port))
            except OSError as exc:
                if exc.errno != errno.EADDRINUSE:
                    raise
                print(f"Portul UDP {udp_ip}:{udp_port} este deja ocupat.", flush=True)
                return

            # Primire numar de discuri pentru jocul "turnurile din Hanoi"
            data, addr = udp_socket.recvfrom(BUFFER_SIZE)
            num_discuri = int(data.decode())
            print(f"Numar de discuri primit de la client: {num_discuri}", flush=True)

            # Initializare starea tijelor
            tije = [list(range(num_discuri, 0, -1)), [], []]
            print(f"Starea initiala a tijelor: {tije}", flush=True)

            while True:
                data, addr = udp_socket.recvfrom(BUFFER_SIZE)
                move = data.decode().strip()
                if move == "STOP":
                    print("Clientul a trimis STOP. Inchidere conexiune.", flush=True)
                    break
                try:
                    src, dest = map(int, move.split())
                    if not (1 <= src <= 3 and 1 <= dest <= 3):
                        raise ValueError("Tijele trebuie numerotate de la 1 la 3")
                    if tije[src-1] and (not tije[dest-1] or tije[src-1][-1] < tije[dest-1][-1]):
                        tije[dest-1].append(tije[src-1].pop())
                        response = f"Starea tijelor pentru {udp_ip}:{udp_port}: {tije}"
                    else:
                        response = "Mutare invalida"
                except (ValueError, IndexError):
                    response = "Format mutare invalid"

                # Verificare daca jocul s-a incheiat
                if tije[2] == list(range(num_discuri, 0, -1)):
                    response = f"Joc incheiat! Starea finala a tijelor pentru {udp_ip}:{udp_port}: {tije}"
                    udp_socket.sendto(response.encode(), addr)
                    print(f"Clientul {udp_ip}:{udp_port} a castigat jocul!", flush=True)
                    udp_socket.close()
                    break

                else:
                    udp_socket.sendto(response.encode(), addr)



TCP_IP = '127.0.0.1'
TCP_PORT = 12345
BUFFER_SIZE = 1024

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as tcp_socket:
    tcp_socket.bind((TCP_IP, TCP_PORT))
    tcp_socket.listen(5)

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