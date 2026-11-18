# Clientul alege un port UDP liber pe calculatorul său, creează un socket UDP și îl leagă la portul ales. 
# Apoi se conectează prin TCP la server și îi transmite numărul portului.
# Serverul creează un socket UDP pentru sesiunea curentă și încearcă să îl lege la același număr de port, pe propria adresă IP. 
# Serverul confirmă prin TCP dacă portul este disponibil. Dacă portul este ocupat, clientul poate alege altul. 
# După confirmare, conexiunea TCP se închide.
# Clientul trimite la adresa IP a serverului, pe portul confirmat, o singură datagramă care conține numărul de elemente și șirul de cel mult 100 de numere întregi.
# Serverul calculează suma numerelor prime din șir și o trimite de pe același socket UDP la adresa IP a clientului, pe același număr de port. 
# Dacă șirul nu conține numere prime, serverul trimite 0. Clientul primește și afișează rezultatul.
# Serverul deservește clienții pe rând. După ce trimite rezultatul, închide socketul UDP al sesiunii și revine la accept() pentru a prelua următorul client.

def is_prime(n):
    if n < 2:
        return False
    for i in range(2, n//2 + 1):
        if n % i == 0:
          return False
    return True

import socket

TCP_PORT = 12345  # Portul TCP pe care serverul îl ascultă pentru conexiuni inițiale de la client
TCP_IP = '0.0.0.0'  # Adresa IP pe care serverul o ascultă pentru conexiuni TCP inițiale de la client

tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp_socket.bind((TCP_IP, TCP_PORT))
tcp_socket.listen(5)  # Ascultă pentru conexiuni TCP inițiale de la client

while True:
    conn, addr = tcp_socket.accept()  # Acceptă conexiunea TCP inițială de la client
    print(f"Conexiune TCP acceptată de la {addr}")
    data = conn.recv(1024)  # Primește numărul portului UDP de la client
    udp_port = int(data.decode().strip())
    print(f"Port UDP solicitat de client: {udp_port}")
    conn.close()  # Închide conexiunea TCP inițială

    # Crearea socketului UDP pentru sesiunea curentă
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        udp_socket.bind(('0.0.0.0', udp_port))
        print(f"Socket UDP legat la portul {udp_port}")
    except OSError:
        print(f"Portul UDP {udp_port} este ocupat")
        continue  # Așteaptă următorul client

    # Primirea datagramei UDP de la client
    data, client_addr = udp_socket.recvfrom(1024)
    message = data.decode().strip()
    print(f"Mesaj UDP primit de la {client_addr}: {message}")

    # Procesarea mesajului pentru a calcula suma numerelor prime
    parts = message.split()
    count = int(parts[0])
    numbers = list(map(int, parts[1:1+count]))

    prime_sum = sum(n for n in numbers if is_prime(n))
    udp_socket.sendto(str(prime_sum).encode(), client_addr)
    udp_socket.close()