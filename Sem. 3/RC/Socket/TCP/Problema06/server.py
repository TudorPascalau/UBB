
import socket

TCP_IP = '0.0.0.0'
TCP_PORT = 7000

BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(5)

while True:
    conn, addr = s.accept()
    print("Connection from:", addr)

    data = conn.recv(BUFFER_SIZE)
    message = data.decode()
    print("Received message:", message)

    data = conn.recv(1)
    character = data.decode()
    print("Received character:", character)

    positions = [i for i in range(len(message)) if message[i] == character]
    positions_str = ', '.join(map(str, positions)) + '\n'
    conn.send(positions_str.encode())

    conn.close()