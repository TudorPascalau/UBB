import os
import signal
import socket
from multiprocessing import Lock

tastatura = Lock()


def cuvant_valid(cuvant, anterior):
    return len(cuvant) >= 2 and len(anterior) >= 2 and cuvant[:2] == anterior[-2:]


def deservire_client(client_tcp_socket):
    with client_tcp_socket:
        with client_tcp_socket.makefile("rb") as flux:
            udp_ip, port_text = flux.read(256).decode().split()
            udp_port = int(port_text)
            if not 1 <= udp_port <= 65535:
                raise ValueError("Port UDP invalid")

    server_udp_addr = (udp_ip, udp_port)

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_socket:
        with tastatura:
            cuvant = input(f"Introduceti primul cuvant pentru {udp_ip}:{udp_port}: ")
        udp_socket.sendto(cuvant.encode(), server_udp_addr)

        while True:
            data, _ = udp_socket.recvfrom(1024)
            raspuns = data.decode()
            print(f"Cuvant primit de la serverul UDP: {raspuns}", flush=True)

            if not cuvant_valid(raspuns, cuvant):
                udp_socket.sendto(b"STOP", server_udp_addr)
                break

            with tastatura:
                cuvant = input(f"Introduceti urmatorul cuvant pentru {udp_ip}:{udp_port}: ")

            if not cuvant_valid(cuvant, raspuns):
                udp_socket.sendto(b"STOP", server_udp_addr)
                break

            udp_socket.sendto(cuvant.encode(), server_udp_addr)


signal.signal(signal.SIGCHLD, signal.SIG_IGN)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as tcp_socket:
    tcp_socket.bind(("0.0.0.0", 5005))
    tcp_socket.listen(5)

    while True:
        client_tcp_socket, client_addr = tcp_socket.accept()

        try:
            pid = os.fork()
        except OSError as eroare:
            client_tcp_socket.close()
            print(f"{client_addr}: {eroare}", flush=True)
            continue

        if pid == 0:
            tcp_socket.close()
            try:
                deservire_client(client_tcp_socket)
            except (OSError, ValueError, EOFError) as eroare:
                print(f"{client_addr}: {eroare}", flush=True)
                os._exit(1)
            os._exit(0)

        client_tcp_socket.close()