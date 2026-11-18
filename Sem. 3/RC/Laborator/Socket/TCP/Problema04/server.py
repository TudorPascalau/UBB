# Un client trimite unui server doua siruri de caractere ordonate. Serverul va interclasa cele doua siruri si va returna clientului sirul rezultat interclasat.

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
        break
    str1, str2 = data.decode().split()
    interleaved = [x for p in zip(str1, str2) for x in p]
    result = ''.join(interleaved)
    conn.send(result.encode())
    conn.close()