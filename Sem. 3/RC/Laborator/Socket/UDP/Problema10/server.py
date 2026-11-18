# Un client trimite unui server un nume de calculator sub forma unui sir de caractere de lungime cel mult 100. 
# Serverul va returna clientului un numar reprezentat pe 4 octeti fara semn ce reprezinta adresa IP a calculatorului respectiv. 
# Clientul va afisa corespunzator adresa IP (in format zecimal cu “.”) sau un mesaj de eroare daca numele calculatorului nu poate fi translatat intr-o adresa IP.
# Se comunica prin UDP.

import socket
import struct
import sys
import socket
import struct

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind(("0.0.0.0", 5005))

while True:
    data, client_addr = server_socket.recvfrom(1024)
    hostname = data.decode().strip()
    try:
        ip_address = socket.gethostbyname(hostname)
        ip_packed = socket.inet_aton(ip_address)
        server_socket.sendto(ip_packed, client_addr)
    except socket.gaierror:
        server_socket.sendto(b'\x00\x00\x00\x00', client_addr)
