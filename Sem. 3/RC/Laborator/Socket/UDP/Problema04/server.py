# Un client trimite unui server un sir de lungime cel mult 100 de caractere. Serverul va returna clientului acest sir oglindit (caracterele sirului in ordine inversa).
# Se comunica prin UDP

import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind(("127.0.0.1", 2020))

while True:
    message, client_address = server_socket.recvfrom(1024)
    message = message.decode()
    reversed_message = message[::-1]
    server_socket.sendto(reversed_message.encode(), client_address)