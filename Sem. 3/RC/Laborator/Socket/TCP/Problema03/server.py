# Un client trimite unui server un sir de caractere. Serverul va returna clientului acest sir oglindit (caracterele sirului in ordine inversa).

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
    reversed_data = data[::-1]
    conn.send(reversed_data)
    conn.close()