#if 0
!/bin/sh
gcc -Wall `sdl-config --cflags` tcps.c -o tcps `sdl-config --libs` -lSDL_net

exit
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "SDL2/SDL_net.h"
//#include "SDL2_net.h"
#include "point.h"

#define MAX_NR_OF_CLIENTS 4

struct client
{
	TCPsocket sock;
	int playerNr;
};
typedef struct client Client;

Client createClient(TCPsocket sock, Client clients[], int playerNr);
SDLNet_SocketSet createSockSet(int nrOfClients, Client clients[], TCPsocket server);
void catGenerator(int catNumber[]);

int main(int argc, char **argv)
{ 
	int catNumber[MAX_NR_OF_CLIENTS] = {0};
	TCPsocket sd, csd; /* Socket descriptor, Client socket descriptor */
	IPaddress ip;
	SDLNet_SocketSet set; 
	Uint16 port;
	port = (Uint16)strtol(argv[1],NULL,0); //takes first argument and uses as port nr

	Client clients[MAX_NR_OF_CLIENTS]; //array of structs for clients
	int nrOfClients = 0;

	if(SDLNet_Init() < 0) 
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError()); 
		exit(EXIT_FAILURE); 
	}

	/* Resolving the host using NULL make network interface to listen */ 
	if(SDLNet_ResolveHost(&ip, NULL, port) < 0) 
	{ 
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError()); exit(EXIT_FAILURE); 
	}

	/* Open a connection with the IP provided (listen on the host's port) */ 
	if(!(sd = SDLNet_TCP_Open(&ip))) 
	{ 
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError()); exit(EXIT_FAILURE); 
	}

	printf("SERVER READY\n");

	catGenerator(catNumber); //fill array with numbers 1-5 at random index

	while(nrOfClients < MAX_NR_OF_CLIENTS) 
	{ 
		/* This check the sd if there is a pending connection. * If there is one, accept that, and open a new socket for communicating */ 
		set = createSockSet(nrOfClients, clients, sd);

		if((csd = SDLNet_TCP_Accept(sd))) //if client and server connected...
		{ 
			//we can communicate with the client using csd socket * sd will remain opened waiting other connections */
			clients[nrOfClients] = createClient(csd, clients, catNumber[nrOfClients]); //add client and increment nr of clients
			
			printf("CLIENT %d REGISTERED - player #%d\n", nrOfClients+1, clients[nrOfClients].playerNr);
			
			if(SDLNet_TCP_Send(csd, &clients[nrOfClients].playerNr, 512) > 0) //send information about which cat the client will control
			{
				printf("Client %d recieved player information\n", nrOfClients+1);
			}			

			nrOfClients++;	
		}		
	} 

	printf("Maximum number of players reached\n");

	SDLNet_TCP_Close(csd); //close client sock
	SDLNet_TCP_Close(sd); //close server
	SDLNet_Quit();

	return 0;
}

Client createClient(TCPsocket sock, Client clients[], int playerNr)
{
	Client c;
	c.playerNr = playerNr;
	c.sock = sock;
	
	return c;
}

SDLNet_SocketSet createSockSet(int nrOfClients, Client clients[], TCPsocket server)
{
	static SDLNet_SocketSet set = NULL;

	if(set)
	{
		SDLNet_FreeSocketSet(set);
	}	

	set = SDLNet_AllocSocketSet(nrOfClients+1);

	if(!set)
	{
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(1); /*most of the time this is a major error, but do what you want. */
	}

	SDLNet_TCP_AddSocket(set, server);

	for(int i = 0; i < nrOfClients; i++)
	{
		SDLNet_TCP_AddSocket(set, clients[i].sock); 
	}
		
	return(set);
}

void catGenerator(int catNumber[])
{
    srand(time(NULL));
	
	for(int loop = 0; loop < MAX_NR_OF_CLIENTS; loop++)
	{
		catNumber[loop] = rand()%4+1;
		int x = catNumber[loop];

		for(int i = 0; i < MAX_NR_OF_CLIENTS; i++)
		{
			if(x == catNumber[i] && i != loop)
			{
				loop--;
				break;
			}
		}
	}

	return;
}




