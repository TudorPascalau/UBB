import socket
import os

def deservire_client(conn):
    data = conn.recv(BUFFER_SIZE)
    message = data.decode()
    if data:
        print("Received message from client:", message)
        
    data = conn.recv(2)
    subseq_lenght = int(data.decode())
    if subseq_lenght:
        print("Received subsequence length from client:", subseq_lenght)

TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)
while True:
    conn, addr = s.accept()
    print('Connection address:', addr)
    deservire_client(conn)
    conn.close()