import socket

TCP_IP = "127.0.0.1"
TCP_PORT = 1234


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

a = int(input("a = "))
b = int(input("b = "))
s.sendall(f"{a} {b}".encode())

suma = int(s.recv(1024).decode())
print("Suma primita de la server:", suma)
s.close()
