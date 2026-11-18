# Un client trimite unui server doua siruri de caractere. 
# Serverul ii raspunde clientului cu caracterul care se regaseste de cele mai multe ori pe pozitii identice in cele doua siruri si cu numarul de aparitii ale acestui caracter.

import socket
import os

def deservire_client(conn):
    data1 = conn.recv(BUFFER_SIZE)
    data2 = conn.recv(BUFFER_SIZE)

    str1 = data1.decode()
    str2 = data2.decode()
    counter = {}
    for c1, c2 in zip(str1, str2):
        if c1 == c2:
            counter[c1] = counter.get(c1, 0) + 1
    if counter:
        max_char = max(counter, key=counter.get)
        result = f"{max_char} {counter[max_char]}"
    else:
        result = ""
    conn.sendall(result.encode())
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