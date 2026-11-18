import socket
import os

def deservire_client(conn):
    data = conn.recv(BUFFER_SIZE)
    numbers_string = data.decode()
    numbers_first = [int(x) for x in numbers_string.split()]
    print("Received numbers:", numbers_first)

    data = conn.recv(BUFFER_SIZE)
    numbers_string = data.decode()
    numbers_second = [int(x) for x in numbers_string.split()]
    print("Received numbers:", numbers_second)

    result = [x for x in numbers_first if x in numbers_second]
    conn.sendall(" ".join(map(str, result)).encode())

    conn.close()

TCP_IP = '0.0.0.0'
TCP_PORT = 5005

BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(5)

while True:
    conn, addr = s.accept()
    print("Connection from:", addr)

    if os.fork() == 0:
        deservire_client(conn)
        os._exit(0)
    conn.close()