# Se cere realizarea unei aplicații client–server care simulează jocul „fazan” între un server TCP și unul sau mai mulți clienți TCP. 
# Aplicația folosește TCP pentru inițializarea sesiunilor și UDP pentru desfășurarea jocului.
# Fiecare client TCP deschide un socket UDP pe care va asculta, se conectează la serverul TCP și îi transmite adresa IP și portul acelui socket. 
# După primirea acestor informații, serverul închide conexiunea TCP cu clientul respectiv.
# După etapa TCP, rolurile se inversează. 
# Fostul client TCP devine server UDP și așteaptă datagrame pe portul comunicat. 
# Fostul server TCP devine client UDP și inițiază jocul trimițând un cuvânt la adresa și portul primite.
# Serverul UDP răspunde cu un cuvânt care începe cu ultimele două litere ale cuvântului primit. 
# Clientul UDP citește apoi un cuvânt de la tastatură și verifică dacă acesta începe cu ultimele două litere ale răspunsului. 
# Dacă regula este respectată, clientul UDP trimite cuvântul și jocul continuă. 
# În caz contrar, clientul UDP trimite automat mesajul STOP și încheie sesiunea respectivă. 
# La primirea mesajului STOP, serverul UDP încheie și el sesiunea.
# Serverul TCP trebuie să accepte mai mulți clienți simultan, folosind fork(). 
# Pentru fiecare conexiune acceptată, un proces copil gestionează schimbul inițial prin TCP și continuă jocul în rolul de client UDP. 
# Procesul părinte rămâne disponibil pentru a accepta noi conexiuni TCP.
# Toate mesajele jocului, inclusiv STOP, sunt transmise exclusiv prin UDP. 
# Aplicația trebuie să valideze cuvintele, să trateze erorile de comunicare și să elibereze resursele la încheierea fiecărei sesiuni.

import errno
import socket


# Citire adresa IP si port UDP de la tastatura
udp_ip = input("Introduceti adresa IP UDP: ")
udp_port = int(input("Introduceti portul UDP: "))

# Creare socket UDP pentru a asculta pe adresa si portul specificate
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
try:
    udp_socket.bind((udp_ip, udp_port))
except OSError as eroare:
    udp_socket.close()
    print(f"Nu se poate folosi adresa UDP {udp_ip}:{udp_port} ({eroare}).")
    raise SystemExit(1)


# Conectare la serverul TCP
TCP_SERVER_IP = '127.0.0.1'
TCP_SERVER_PORT = 5005

tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp_socket.connect((TCP_SERVER_IP, TCP_SERVER_PORT))

# Trimitere adresei IP si portului UDP catre serverul TCP
tcp_socket.send(f"{udp_ip} {udp_port}".encode())
tcp_socket.close()  # Inchidere conexiune TCP dupa trimiterea informatiilor UDP

try:
    while True:
        data, addr = udp_socket.recvfrom(1024)
        mesaj = data.decode()

        if mesaj == "STOP":
            print("Clientul UDP a trimis STOP. Incheiem sesiunea.")
            break

        print(f"Cuvant primit: {mesaj}")
        cuvant = input("Introduceti urmatorul cuvant: ")
        udp_socket.sendto(cuvant.encode(), addr)
except socket.timeout:
    print("Nu am primit un raspuns UDP la timp.")
except (OSError, EOFError, UnicodeError) as eroare:
    print(f"Sesiunea s-a incheiat ({eroare}).")
finally:
    udp_socket.close()





