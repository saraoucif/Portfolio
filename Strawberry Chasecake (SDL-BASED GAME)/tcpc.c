#if 0
#!/bin/sh
gcc -Wall `sdl-config --cflags` tcps.c -o tcps `sdl-config --libs` -lSDL_net

exit
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_net.h>
#include "point.h"

#define MAX_NR_OF_CLIENTS 4

int tcpClient(int argc, char **argv)
{
	TCPsocket sd, csd; 				/* Socket descriptor, Client socket descriptor */
	IPaddress ip, *remoteIP;
	int quit, quit2;
	char buffer[512] = "hej";
	SDLNet_SocketSet set;
	Uint16 port;
	port=(Uint16)strtol(argv[2],NULL,0);
	int catnr, nrOfClients = 0;
	int temp[20];
 
	if(SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	set=SDLNet_AllocSocketSet(1);
	if(!set)
	{
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		SDLNet_Quit();
		SDL_Quit();
		exit(4); /*most of the time this is a major error, but do what you want. */
	}
 
	/* Resolving the host using input arguments to make connection to network interface */
	if(SDLNet_ResolveHost(&ip, argv[1], port) == -1)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Open a connection with the IP provided (listen on the host's port) */
	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	//if adding socket failed...
	if(SDLNet_TCP_AddSocket(set, sd) == -1) 
	{
		printf("SDLNet_TCP_AddSocket: %s\n",SDLNet_GetError());
		SDLNet_Quit();
		SDL_Quit();
		exit(7);
	}

	printf("CONNECTION ESTABLISHED\n");

	if(SDLNet_TCP_Recv(sd, &catnr, 512) > 0)
	{
		printf("I am player #%d\n", catnr);
	}

	return catnr;
} 