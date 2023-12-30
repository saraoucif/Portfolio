#if 0
#!/bin/sh
gcc -Wall `sdl-config --cflags` udps.c -o udps `sdl-config --libs` -lSDL_net
 
exit
#endif
 
#include <stdio.h>
#include <string.h>
#include "point.h"
#include <SDL2/SDL_net.h>

#define MAX 4

struct data
{
   int x;
   int y;
   int frame;
   int catNumber;
   SDL_RendererFlip flip;
   int playAgain;
   int newPoint;
   int caught;
   int indexForPoints;
};
typedef struct data Data;

struct client
{
    Uint32 IP;
    Uint32 port;
}; 
typedef struct client Client;

void sendInfoToClients(Client clients[], UDPsocket, UDPpacket *pSent, UDPpacket *pRecieve,Data udpData, int i);

int main(int argc, char **argv)
{
	UDPsocket sd;              /* Socket descriptor */
	UDPpacket *pReceive;       /* Pointer to packet memory */
	UDPpacket *pSent;
    IPaddress srvadd;
    Uint16 port;
    port = (Uint16)strtol(argv[1],NULL,0);

    Client clients[MAX]={0};

    Data udpData; 
    int index = 0;
    
	/* Initialize SDL_net */
	if(SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Open a socket */
	if(!(sd = SDLNet_UDP_Open(2000)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Make space for the packet */
	if(!((pSent = SDLNet_AllocPacket(512)) && (pReceive = SDLNet_AllocPacket(512))))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

    printf("UDP IS OPEN\n");

	/* Main loop */
	while (1)
	{
		/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
		if(SDLNet_UDP_Recv(sd, pReceive))
		{
            printf("RECEIVED\n");
		
            if(clients[0].IP == 0 && clients[0].port == 0)
            {
                printf("Client 1\n");
                clients[0].IP= pReceive->address.host;
                clients[0].port = pReceive->address.port;
            }
            else if(pReceive->address.port != clients[0].port && clients[1].IP == 0)
            {
                printf("Client 2\n");
                clients[1].IP= pReceive->address.host;
                clients[1].port = pReceive->address.port;
            }
            else if(pReceive->address.port != clients[0].port && pReceive->address.port != clients[1].port && clients[2].IP == 0)
            {
                printf("Client 3\n");
                clients[2].IP= pReceive->address.host;
                clients[2].port = pReceive->address.port;
            }
            else if(pReceive->address.port != clients[0].port && pReceive->address.port != clients[1].port && pReceive->address.port != clients[2].port && clients[3].IP == 0)
            {
                printf("Client 4\n");
                clients[3].IP= pReceive->address.host;
                clients[3].port = pReceive->address.port;
            }
            else
            {
                if(pReceive->address.port == clients[0].port)
                {
                    for(int i = 1; i < MAX; i++)
                    {
                        if(clients[i].IP != 0)
                        {
                            sendInfoToClients(clients, sd, pSent, pReceive, udpData, i);
                        }
                            
                    }
                }
                else if (pReceive->address.port == clients[1].port)
                {
                    for(int i=0; i<MAX; i++)
                    {
                        if(clients[i].IP != 0 && i != 1)
                        {
                            sendInfoToClients(clients, sd, pSent, pReceive, udpData, i);
                        }
                            
                    }
                }
                else if (pReceive->address.port == clients[2].port)
                {
                    for(int i=0; i<MAX; i++)
                    {
                        if(clients[i].IP != 0 && i != 2)
                        {
                            sendInfoToClients(clients, sd, pSent, pReceive, udpData, i);
                        }
                            
                    }
                }
                else if (pReceive->address.port == clients[3].port)
                {
                    for(int i=0; i<MAX; i++)
                    {
                        if(clients[i].IP != 0 && i != 3)
                        {
                            sendInfoToClients(clients, sd, pSent, pReceive, udpData, i);
                        } 
                    }
                }
            }
		}		
	}
 
	/* Clean and exit */
	SDLNet_FreePacket(pSent);
    SDLNet_FreePacket(pReceive);
	SDLNet_Quit();

	return EXIT_SUCCESS;
} 

void sendInfoToClients(Client clients[], UDPsocket sd, UDPpacket *pSent, UDPpacket *pReceive, Data udpData, int i)
{
    int a, b, c, d, e, f, g, h, j;
    printf("Send to Client %d\n", i);
    pSent->address.host = clients[i].IP;	/* Set the destination host */
    pSent->address.port = clients[i].port;  /* Set the destination port */
    sscanf((char * )pReceive->data, "%d %d %d %d %d %d %d %d %d\n", &a, &b, &c, &d, &e, &f, &g, &h, &j);
    sprintf((char *)pSent->data, "%d %d %d %d %d %d %d %d %d\n", a,  b, c, d, e, f, g, h, j);
    memcpy(&udpData, (char * ) pReceive->data, sizeof(Data));
    printf("UDP Packet data %d %d %d %d %d %d %d %d %d\n", udpData.x, udpData.y, udpData.frame, udpData.catNumber, udpData.flip, udpData.playAgain, udpData.newPoint, udpData.caught, udpData.indexForPoints);
    memcpy((char *)pSent->data, &udpData , sizeof(Data)+1);
    pSent->len = sizeof(Data)+1;
    SDLNet_UDP_Send(sd, -1, pSent);
}