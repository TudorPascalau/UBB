# Un client trimite unui server un numar reprezentat pe un octet fara semn. 
# Serverul va returna clientului sirul divizorilor acestui numar.
# Se comunica prin UDP

import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 2020

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((UDP_IP, UDP_PORT))
while True:
    message, client_address = server_socket.recvfrom(1)
    number = int.from_bytes(message, byteorder='big')
    divisors = [str(i) for i in range(1, number + 1) if number % i == 0]
    divisors_str = " ".join(divisors)
    server_socket.sendto(divisors_str.encode(), client_address)