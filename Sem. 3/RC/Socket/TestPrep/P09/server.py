

import errno
import socket
import os
import random

def deservire_client(conn):

    # Citire IP si port UDP de la client
    udp_info = conn.recv(BUFFER_SIZE).decode()
    udp_ip, udp_port = udp_info.split()
    udp_port = int(udp_port)

    # udp_ip si udp_port reprezinta adresa clientului UDP
    if not 1 <= udp_port <= 65534:
        print("Port UDP invalid.", flush=True)
        return
    
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_socket:
            try:
                udp_socket.bind(("127.0.0.1", udp_port + 1))
            except OSError as exc:
                if exc.errno != errno.EADDRINUSE:
                    raise
                print(f"Portul UDP 127.0.0.1:{udp_port + 1} este deja ocupat.", flush=True)
                return

            # Generare cuvant aleator de ghicit
            words = ["python", "socket", "programming", "network", "communication"]
            secret_word = random.choice(words)
            print(f"Cuvantul secret pentru clientul {udp_ip}:{udp_port} este: {secret_word}", flush=True)

            # Incepe jocul "Ghicit cuvant" prin UDP
            while True:
                buffer, addr = udp_socket.recvfrom(BUFFER_SIZE)
                message = buffer.decode().strip()
                if message == "STOP":
                    print(f"Clientul {udp_ip}:{udp_port} a oprit jocul.", flush=True)
                    break
                if message == secret_word:
                    response = "Felicitari! Ati ghicit cuvantul!"
                    udp_socket.sendto(response.encode(), (udp_ip, udp_port))
                    print(f"Clientul {udp_ip}:{udp_port} a ghicit cuvantul.", flush=True)
                    break
                else:
                    response = "Cuvant gresit. Incercati din nou."
                    udp_socket.sendto(response.encode(), (udp_ip, udp_port))
            print(f"Clientul {udp_ip}:{udp_port} a terminat jocul.", flush=True)



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