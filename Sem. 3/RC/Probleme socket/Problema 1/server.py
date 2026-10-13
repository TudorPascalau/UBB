import socket

TCP_IP = "0.0.0.0"
TCP_PORT = 1234


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(5)

while True:
    conn, addr = s.accept()
    print("Client conectat:", addr)
    data = conn.recv(1024).decode()
    a, b = map(int, data.split())
    print("Numere primite:", a, b)
    suma = a + b
    conn.sendall(str(suma).encode())
    conn.close()
