#Enunt: Clientul trimite serverului un numar. Serverul il primeste si il afiseaza pe ecran.
#
#Rulare in doua terminale diferite:
#	python server.py
#	python client.py
import socket

TCP_IP = "172.30.240.138"
TCP_PORT = 8889
MESSAGE = str(input("Dati un numar: "))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
s.send(MESSAGE.encode())
print("Am trimis la server: ", MESSAGE)
s.close()
