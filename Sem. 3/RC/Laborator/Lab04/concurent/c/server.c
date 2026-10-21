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
#include <time.h>
#include <stdlib.h>

void deservire_client(int newSocket,uint16_t nr, uint16_t r) {
	uint16_t length,incercari=0;
	
  char mic[]="MAI MIC";
  char mare[]="MAI MARE";
  char egal[]="EGAL";
  while (nr != r) {
	  printf("inainte de recv\n");	
	  recv(newSocket, &nr, sizeof(uint16_t), 0);						/* Read the message from the server into the buffer */
	  nr=ntohs(nr);	
	  printf("Data received: %hu\n",nr);   					/* Print the received message */
	  
	  if(nr<r)  {
		  length=htons(strlen(mic));
		  printf("Trimit %hu,%s\n",strlen(mic),mic);
		  send(newSocket,&length,sizeof(uint16_t),0);
		  length=ntohs(length);
		  send(newSocket,mic,length*sizeof(char),0);
		  incercari++;
	  }

	  if(nr==r)  {
		  length=htons(strlen(egal));
		  printf("Trimit %hu,%s\n",strlen(egal),egal);
		  send(newSocket,&length,sizeof(uint16_t),0);
		  length=ntohs(length);
		  send(newSocket,egal,length*sizeof(char),0);
		  incercari++;
	  } 

	  if(nr>r)  {
		  length=htons(strlen(mare));
		  printf("Trimit %hu,%s\n",strlen(mare),mare);
		  send(newSocket,&length,sizeof(uint16_t),0);
		  length=ntohs(length);
		  send(newSocket,mare,length*sizeof(char),0);
		  incercari++;
	  }
	  printf("nr=%hu, r=%hu\n",nr,r);	
  }
  printf("Nr de incercari=%hu\n",incercari);
  incercari=htons(incercari);
  send(newSocket,&incercari,sizeof(int),0);
  
  close(newSocket);
}

int main(){
  int welcomeSocket, newSocket;
  uint16_t nr, rez, length;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  srand(time(NULL));   // should only be called once for random number  
  int r;      // returns a pseudo-random integer between 0 and 19
  uint16_t incercari=0;  
  
  welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);				/* Create the socket. The three arguments are:  1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  
  serverAddr.sin_family = AF_INET;						/* Address family = Internet */
  serverAddr.sin_port = 8888;							/* Set port number*/
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");				/* Set IP address to localhost */

  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));	/* Bind the address struct to the socket */

  listen(welcomeSocket,5);							/* Listen on the socket, with 5 max connection requests queued */

  addr_size = sizeof serverStorage;
  while(1)
  {
	  incercari=0;
	  r = rand() % 20;      // returns a pseudo-random integer between 0 and 19
	  nr=21;
	  printf("S-a generat %d\n",r);  
	newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  
	  printf("S-a conectat un client... nr=%hu, r=%hu\n",nr,r);
	   if (fork() == 0) { // fiu
      deservire_client(newSocket,nr,r);
      return 0;
    }
  }
  close(welcomeSocket);

  return 0;
}