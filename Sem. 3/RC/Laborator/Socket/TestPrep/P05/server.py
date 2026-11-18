# Se cere realizarea unei aplicatii client-server care simuleaza jocul „fazan”.
# Programul C gestioneaza mai multe jocuri simultan, cate unul pentru fiecare
# proces copil creat cu fork(). Fiecare copil deschide un socket UDP pe un port
# distinct, se conecteaza la serverul TCP corespunzator si ii transmite IP-ul
# si portul UDP. Apoi inchide conexiunea TCP si devine server UDP.
#
# Fostul server TCP devine client UDP si trimite primul cuvant. Serverul UDP
# citeste un raspuns de la tastatura si il trimite clientului UDP. Fiecare
# cuvant trebuie sa inceapa cu ultimele doua litere ale cuvantului anterior.
# Clientul UDP verifica atat raspunsul primit, cat si urmatorul cuvant citit
# de la tastatura. La prima abatere trimite STOP si incheie jocul.
# Serverul UDP incheie sesiunea cand primeste STOP.
#
# Serverele TCP sunt secventiale si citesc IP-ul si portul local de la tastatura.

import socket


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
        cuvant = input("Introduceti primul cuvant: ")
        udp_socket.sendto(cuvant.encode(), server_udp_addr)

        while True:
            date, _ = udp_socket.recvfrom(1024)
            raspuns = date.decode()
            print(f"Cuvant primit de la serverul UDP: {raspuns}")

            if not cuvant_valid(raspuns, cuvant):
                udp_socket.sendto(b"STOP", server_udp_addr)
                break

            cuvant = input("Introduceti urmatorul cuvant: ")
            if not cuvant_valid(cuvant, raspuns):
                udp_socket.sendto(b"STOP", server_udp_addr)
                break

            udp_socket.sendto(cuvant.encode(), server_udp_addr)


tcp_ip = input("Introduceti IP-ul local al serverului TCP: ")
tcp_port = int(input("Introduceti portul local al serverului TCP: "))

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as tcp_socket:
    tcp_socket.bind((tcp_ip, tcp_port))
    tcp_socket.listen(5)

    while True:
        client_tcp_socket, client_addr = tcp_socket.accept()
        try:
            deservire_client(client_tcp_socket)
        except (OSError, ValueError) as eroare:
            print(f"{client_addr}: {eroare}")
        except EOFError:
            break
        except KeyboardInterrupt:
            print("Serverul TCP a fost oprit.")
            break