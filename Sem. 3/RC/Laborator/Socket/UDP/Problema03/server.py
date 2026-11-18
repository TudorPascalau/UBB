# Un client trimite unui server un sir de lugime cel mult 100 de caractere. Serverul va returna clientului numarul de caractere spatiu din sir.
# Se comunica prin UDP

import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 2020

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = server_socket.recvfrom(1024)
    message = data.decode()
    space_count = message.count(' ')
    server_socket.sendto(str(space_count).encode(), addr)