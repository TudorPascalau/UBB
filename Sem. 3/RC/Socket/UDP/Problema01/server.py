# Un client trimite unui server doua numere. Serverul va returna clientului suma celor doua numere.
# Se comunica prin UDP

import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 2020

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((UDP_IP, UDP_PORT))

# We are getting the numbers separately, each as a 4-byte integer
while True:
    data1, addr = server_socket.recvfrom(4)
    data2, addr = server_socket.recvfrom(4)
    if len(data1) == 4 and len(data2) == 4:
        try:
            num1 = int.from_bytes(data1, byteorder='big')
            num2 = int.from_bytes(data2, byteorder='big')
            result = num1 + num2
            server_socket.sendto(result.to_bytes(4, byteorder='big'), addr)
        except ValueError:
            server_socket.sendto(b"Invalid numbers", addr)
    else:
        server_socket.sendto(b"Invalid input", addr)
