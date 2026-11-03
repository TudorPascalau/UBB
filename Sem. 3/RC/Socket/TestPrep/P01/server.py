# Un client trimite serverului un șir de numere întregi. Serverul îi returnează suma numerelor prime din șir. Comunicarea se desfășoară astfel:
# Clientul creează un socket UDP, apoi se conectează prin TCP la server și îi trimite portul UDP pe care așteaptă răspunsuri.
# Serverul îi transmite prin TCP portul propriului socket UDP. Adresele IP se determină din conexiunea TCP.
# Clientul trimite prin UDP o datagramă care conține numărul de elemente și șirul de numere, de lungime cel mult 100.
# Serverul calculează suma numerelor prime și trimite rezultatul prin UDP la adresa IP a clientului și portul comunicat la pasul 1. Dacă șirul nu conține numere prime, rezultatul este 0.
# Clientul afișează rezultatul și trimite prin TCP mesajul STOP, după care ambele părți închid socketurile asociate sesiunii.

import socket
def is_prime(n):
    if n < 2:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

def sum_of_primes(numbers):
    return sum(n for n in numbers if is_prime(n))

TCP_IP = '127.0.0.1'
TCP_PORT = 12345
BUFFER_SIZE = 1024

tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp_sock.bind((TCP_IP, TCP_PORT))
tcp_sock.listen(1)
conn, addr = tcp_sock.accept()
print('Connection address:', addr)

udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udp_sock.bind((TCP_IP, 0))
udp_port = udp_sock.getsockname()[1]
conn.send(str(udp_port).encode())
while True:
    data, client_addr = udp_sock.recvfrom(BUFFER_SIZE)
    numbers = list(map(int, data.decode().split()))
    result = sum_of_primes(numbers)
    udp_sock.sendto(str(result).encode(), client_addr)
    if result == 0:
        print('No prime numbers found in', numbers)
    else:
        print('Sum of prime numbers in', numbers, 'is', result)
    tcp_data = conn.recv(BUFFER_SIZE)
    if tcp_data.decode().strip() == 'STOP':
        break
    
conn.close()
tcp_sock.close()
udp_sock.close()