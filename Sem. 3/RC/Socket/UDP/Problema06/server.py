# Un client trimite unui server un sir de lungime cel mult 100 de caractere si un caracter. Serverul va returna clientului toate pozitiile pe care caracterul primit se regaseste in sir.
# Se comunica prin UDP.

import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(101)
    message = data.decode()
    data, addr = sock.recvfrom(1)
    char = data.decode()
    positions = [str(i) for i, c in enumerate(message) if c == char]
    response = ' '.join(positions)
    sock.sendto(response.encode(), addr)