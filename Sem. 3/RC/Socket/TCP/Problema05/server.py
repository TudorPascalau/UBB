
import socket

TCP_IP = '0.0.0.0'
TCP_PORT = 7000

BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(5)

while True:
    conn, addr = s.accept()
    data = conn.recv(BUFFER_SIZE)
    if not data:
        conn.close()
        continue
    n = int(data.decode())
    div = [i for i in range(1, n + 1) if n % i == 0]
    div_count = len(div)
    conn.send(str(div_count).encode())
    message = " ".join(map(str, div)) + "\n"
    conn.send(message.encode())
    conn.close()