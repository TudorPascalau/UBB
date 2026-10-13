import socket

TCP_IP = '127.0.0.1'
TCP_PORT = 8080

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

message = input("Enter a string: ")
s.send(message.encode())
space_count = int(s.recv(2).decode())
print(f"Number of spaces: {space_count}")
s.close()