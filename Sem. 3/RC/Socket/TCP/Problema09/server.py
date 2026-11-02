import socket
import os

def deservire_client(conn):
    data1 = conn.recv(BUFFER_SIZE)
    data2 = conn.recv(BUFFER_SIZE)

    numbers1 = list(map(int, data1.decode().split()))
    numbers2 = list(map(int, data2.decode().split()))
    result = [x for x in numbers1 if x not in numbers2]
    conn.sendall(" ".join(map(str, result)).encode())
    conn.close()

TCP_IP = '0.0.0.0'
TCP_PORT = 5050

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