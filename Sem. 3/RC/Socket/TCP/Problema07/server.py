import socket
import os

def deservire_client(conn):
    data = conn.recv(BUFFER_SIZE)
    message = data.decode()
    if data:
        print("Received message from client:", message)
        
    data = conn.recv(4)
    subseq_lenght = int.from_bytes(data, byteorder='big', signed=True)
    if subseq_lenght:
        print("Received subsequence length from client:", subseq_lenght)

    data = conn.recv(4)
    start_index = int.from_bytes(data, byteorder='big', signed=True)
    if start_index:
        print("Received start index from client:", start_index)

    if start_index + subseq_lenght <= len(message):
        subseq = message[start_index:start_index + subseq_lenght]
        conn.send(subseq.encode())
    else:
        print("Invalid start index or subsequence length")

TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)
while True:
    conn, addr = s.accept()
    if os.fork() == 0:
        deservire_client(conn)
        conn.close()
        os._exit(0)
    conn.close()