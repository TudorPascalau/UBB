# Un client trimite unui server o cerere prin care ii cere acestuia data si ora curenta. 
# Serverul va returna clientului data sub forma unui intreg ce reprezinta numarul de secunde trecute de la 1 ianuarie 1970. Clientul va afisa corespunzator data pe baza acestui intreg.
# Se comunica prin UDP.

import socket
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("127.0.0.1", 5005))

while True:
    data, addr = sock.recvfrom(1024)
    if data:
        timestamp = int(time.time())
        sock.sendto(str(timestamp).encode(), addr)
        print(f"Trimis timestamp {timestamp} catre {addr}")
        print(f"----------------------------------------")
        print()