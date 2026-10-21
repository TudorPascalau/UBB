/* Enunt: Un server genereaza un numar aleator. 
Acesta primeste numere de la clienti si trimite clientului un mesaj (numar mai mic, mai mare sau egal cu numarul generat aleator). 
La finalul jocului (dupa ce serverul trimite mesajul "EGAL"), serverul trimite clientului numarul de incercari.

Compilare: 
	gcc server.c -o server
	gcc client.c -o client
	
Rulare in doua terminale diferite:
	./server
	./client
*/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  int clientSocket;
  uint16_t nr=-1, length, incercari;
  char buffer[1024]="";
  struct sockaddr_in serverAddr;

  clientSocket = socket(AF_INET, SOCK_STREAM, 0);				/* Create the socket. The three arguments are:  1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  
  serverAddr.sin_family = AF_INET;						/* Address family = Internet */
  serverAddr.sin_port = 8888;							/* Set port number*/
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");				/* Set IP address to localhost */
   
  connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof serverAddr);
 
  while(strcmp(buffer,"EGAL")!=0){
	  printf("Introduceti numarul:\n");
	  scanf("%hu",&nr);
	  printf("Trimit la server %hu\n",nr); 
	  nr=htons(nr);
	  send(clientSocket,&nr,sizeof(uint16_t),0);
		
	  recv(clientSocket, &length, sizeof(uint16_t), 0);						/* Read the message from the server into the buffer */
	  length=ntohs(length);
	  printf("length: %d\n",length);   	
	  recv(clientSocket, buffer, length*sizeof(char), 0);						/* Read the message from the server into the buffer */

	  printf("Data received: %d, %s\n",length,buffer);   					/* Print the received message */
	  if(strcmp(buffer,"EGAL")!=0)memset(buffer,0,strlen(buffer));
 }
 recv(clientSocket, &incercari, sizeof(uint16_t), 0);	
incercari=ntohs(incercari);
printf("Numarul de incercari e: %hu\n",incercari);
  close(clientSocket);

  return 0;
}