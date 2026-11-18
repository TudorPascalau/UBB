import socket

TCP_IP = '0.0.0.0'
TCP_PORT = 8080

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(5)

while True:
    conn, addr = s.accept()
    print("Client connected")
    data = conn.recv(256).decode()
    if not data:
        conn.close()
        continue
    space_count = data.count(' ')
    conn.send(str(space_count).encode())
    conn.close()