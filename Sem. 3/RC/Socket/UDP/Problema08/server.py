# Un client trimite unui server doua numere reprezentate pe doi octeti fara semn fiecare. Serverul va returna clientului cmmdc si cmmmc al numerelor primite.
# Se comunica prin UDP.

import socket

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def lcm(a, b):
    return a * b // gcd(a, b)

UDP_IP = "127.0.0.1"
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(2)
    num1 = int.from_bytes(data, byteorder='big', signed=False)
    data, addr = sock.recvfrom(2)
    num2 = int.from_bytes(data, byteorder='big', signed=False)



    cmmdc = gcd(num1, num2)
    cmmmc = lcm(num1, num2)
    response = f"{cmmdc} {cmmmc}"
    sock.sendto(response.encode(), addr)