#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "world.h"
#include "cat.h"
#include "point.h"
#include "tcpc.h"

#ifdef WIN32 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
#define MENU_SCREEN "resources/MENU.bmp" //Windows computer couldn't load jpeg images
#define CAT1_WINNERSCREEN "resources/WINGOJO.bmp" 
#define CAT2_WINNERSCREEN "resources/WINDAD.bmp" 
#define CAT3_WINNERSCREEN "resources/WINWITCH.bmp" 
#define CAT4_WINNERSCREEN "resources/WINVACAY.bmp" 
#define PLAYAGAIN "resources/LOBBY.bmp" 
#endif
#ifndef WIN32
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#define MENU_SCREEN "resources/MENU.jpg"
#define CAT1_WINNERSCREEN "resources/WINGOJO.jpeg" 
#define CAT2_WINNERSCREEN "resources/WINDAD.jpeg"  
#define CAT3_WINNERSCREEN "resources/WINWITCH.jpeg" 
#define CAT4_WINNERSCREEN "resources/WINVACAY.jpeg" 
#define PLAYAGAIN "resources/LOBBY.JPEG" 
#endif

// GAME LOGIC //
#define SPRITEFRAMES 8
#define STARTFRAME 6
#define NROFCATS 4
#define WORLDTILES 24
#define WINDOWSIZE 640
#define MAXSCORE_CHASINGCAT 3
#define SPEED 6
#define MAXSCORE 5
#define NROFPOINTS 20
#define MENU 1
#define PLAY 2

// DIRECTIONS //
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// IMAGES //
#define CAT1 "resources/GOJACAT.bmp"
#define CAT2 "resources/DADCAT.bmp"
#define CAT3 "resources/WITCHCAT.bmp"
#define CAT4 "resources/SWIMCAT.bmp"
#define CAUGHTCAT "resources/ANGELCAT.bmp"
#define POINT "resources/CAKE.BMP"
#define TILES "resources/TILES.BMP"
#define PINKTREE "resources/PINKTREE.BMP"
#define BERRYBUSH "resources/BERRYBUSH.BMP"
#define BUSH "resources/BUSH.BMP"

#undef main

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

// IMAGE AND RENDERING FUNCTIONS //
bool init(SDL_Renderer **gRenderer, SDL_Window *gWindow);
int menu(SDL_Event e);
void loadMedia(SDL_Renderer *gRenderer, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mTree, SDL_Rect gTreePic[],SDL_Texture **mBush, SDL_Rect gBushPic[],SDL_Texture **mBerryBush, SDL_Rect gBerryBushPic[], SDL_Texture **mPoint, SDL_Rect gPointPic[]);
void loadWinnerAndWaitingScreens(SDL_Renderer *gRenderer, SDL_Texture **mWinnerScreen, SDL_Rect gWinnerScreen[], char winningCat[]);
void loadCat(SDL_Renderer *gRenderer, SDL_Texture **mCharacter, SDL_Rect gArray[], char bmp[]);
void setSpriteClips(SDL_Rect gArray[]);
void renderBackground(SDL_Renderer *gRenderer, SDL_Texture *mTile, SDL_Rect gTiles[]);
void renderTrees(SDL_Renderer *gRenderer, SDL_Texture *mTree, SDL_Rect gTreePic[]);
void renderBushes(SDL_Renderer *gRenderer, SDL_Texture *mBush, SDL_Rect gBushPic[], SDL_Texture *mBerryBush, SDL_Rect gBerryBushPic[]);
void renderPoints(SDL_Renderer *gRenderer, SDL_Texture *mPoint, SDL_Rect gPointPic[], int positionArray[][2], int *pIndex, int *pNewPoint, SDL_Rect pointPosition[]);

// COLLISION DETECTION //
void windowCollision(Cat c);
void pointCollision(Cat cats[], SDL_Rect c1position, SDL_Rect c2position, SDL_Rect c3position, SDL_Rect c4position, SDL_Rect pointPosition, int catNr, int *pNewPoint, int pointArray[][2], int index);
void catCollision(SDL_Rect c1position, SDL_Rect c2position, SDL_Rect c3position, SDL_Rect c4position, int catNr, int *pMoveLock, int *pCaught, int collisionCheck[]);
void resetCollisionCheck(int collisionCheck[]);

// MOVING FUNCTIONS //
void moveCatsUp(int catNr,Cat c1, Cat c2, Cat c3, Cat c4,SDL_RendererFlip *flip1,SDL_RendererFlip *flip2,SDL_RendererFlip *flip3,SDL_RendererFlip *flip4);
void moveCatsDown(int catNr,Cat c1, Cat c2, Cat c3, Cat c4,SDL_RendererFlip *flip1,SDL_RendererFlip *flip2,SDL_RendererFlip *flip3,SDL_RendererFlip *flip4);
void moveCatsLeft(int catNr,Cat c1, Cat c2, Cat c3, Cat c4,SDL_RendererFlip *flip1,SDL_RendererFlip *flip2,SDL_RendererFlip *flip3,SDL_RendererFlip *flip4);
void moveCatsRight(int catNr,Cat c1, Cat c2, Cat c3, Cat c4,SDL_RendererFlip *flip1,SDL_RendererFlip *flip2,SDL_RendererFlip *flip3,SDL_RendererFlip *flip4);
void setAnimationFrame(Cat c, SDL_RendererFlip *flip, int direction);
int moveCat(int catNr, SDL_Renderer *gRenderer, SDL_Event e, Cat cats[], SDL_RendererFlip *flip1,SDL_RendererFlip *flip2,SDL_RendererFlip *flip3,SDL_RendererFlip *flip4, SDL_Rect gPointPic[],SDL_Rect *c1position, SDL_Rect *c2position, SDL_Rect *c3position, SDL_Rect *c4position, SDL_Window *gWindow, int *pMoveLock, int *pNewPoint, int *pIndex, int *pCakeCOunter,int originalArray[][2],int *pPlayAgain, int *pCaughtCounter, int collisionCheck[]);

// GAME LOGIC //
void recUDPCat(Cat c, UDPpacket *packet, Data udpData, SDL_RendererFlip *flip, SDL_Rect *pointPosition,int *pNewPoint);
void playAgain(Cat cats[], SDL_Rect *c1position, SDL_Rect *c2position, SDL_Rect *c3position, SDL_Rect *c4position, SDL_RendererFlip *flip1, SDL_RendererFlip *flip2, SDL_RendererFlip *flip3,SDL_RendererFlip *flip4, int *pNewPoint, int *pIndex, int *pMoveLock, int *pCakeCounter,int *pPlayAgain, int *pCaughtCounter, int collisionCheck[], int catNr);

int main(int argc, char **argv)
{  
	srand(time(NULL));
    Uint16 port;
    port = (Uint16)strtol(argv[2], NULL, 0);    //Get port number from terminal
    int menuChoice = 1, gameState = 1;
    int moveLock = 0, cakeCounter = 0, playAgain = 0, playCounter = 0, playAgainCopy = 0, caught = 0, caughtCounter = 0, gojaSend = 0;
    int collisionCheck[3] = {0};                //Array to check if collison with the chasing cat has happened
    int pointArray[NROFPOINTS][2];              //Array to hold possible positions for points
    getPointPositionArray(pointArray);          //Gets coordinates for points

    int catNr = tcpClient(argc, argv);          //Run tcpClient to receive your cat number
    printf("I am player %d\n", catNr);

    Cat cats[NROFCATS];
    // GOJA CAT (the chasing cat) //
    SDL_Texture *mCat1 = NULL;
    SDL_Rect gCatSheet1[SPRITEFRAMES];
    SDL_RendererFlip flip1 = SDL_FLIP_NONE;
    cats[0] = createCat(32, 576, STARTFRAME, 0);
    SDL_Rect c1position = {getCatPositionX(cats[0]), getCatPositionY(cats[0]), 32, 32};
    // DAD CAT //
    SDL_Texture *mCat2 = NULL;
    SDL_Rect gCatSheet2[SPRITEFRAMES];
    SDL_RendererFlip flip2 = SDL_FLIP_NONE;
    cats[1] = createCat(576, 25, STARTFRAME, 0);
    SDL_Rect c2position = {getCatPositionX(cats[1]), getCatPositionY(cats[1]), 32, 32};
    // WITCH CAT //
    SDL_Texture *mCat3 = NULL;
    SDL_Rect gCatSheet3[SPRITEFRAMES];
    SDL_RendererFlip flip3 = SDL_FLIP_NONE;
    cats[2] = createCat(576, 576, STARTFRAME, 0);
    SDL_Rect c3position = {getCatPositionX(cats[2]), getCatPositionY(cats[2]), 32, 32};
    // VACAY CAT //
    SDL_Texture *mCat4 = NULL;
    SDL_Rect gCatSheet4[SPRITEFRAMES];
    SDL_RendererFlip flip4 = SDL_FLIP_NONE;
    cats[3]= createCat(32, 25, STARTFRAME, 0); 
    SDL_Rect c4position = {getCatPositionX(cats[3]), getCatPositionY(cats[3]), 32, 32};
    // DEAD CAT //
    SDL_Texture *mCaughtCat = NULL;
    SDL_Rect gCaughtCatSheet[SPRITEFRAMES];

    // TREE //
    SDL_Texture *mTree = NULL;
    SDL_Rect gTreePic[1];
    // BUSH //
    SDL_Texture *mBush = NULL;
    SDL_Rect gBushPic[1];
    // BERRY BUSH //
    SDL_Texture *mBerryBush = NULL;
    SDL_Rect gBerryBushPic[1];
    // BACKGROUND //
    SDL_Texture *mTiles = NULL;
    SDL_Rect gTiles[WORLDTILES];
    // POINTS //
    SDL_Texture *mPoint = NULL;
    int index = NROFPOINTS, newPoint = 0;
    SDL_Rect gPointPic[1];
    SDL_Rect pointPosition = {pointArray[index][0], pointArray[index][1], getPointWidth(), getPointHeight()};
    // WINNER SCREENS //
    SDL_Texture *mCat1WinnerScreen = NULL, *mCat2WinnerScreen = NULL, *mCat3WinnerScreen = NULL, *mCat4WinnerScreen = NULL;
    SDL_Rect gCat1WinnerScreen[1], gCat2WinnerScreen[1], gCat3WinnerScreen[1], gCat4WinnerScreen[1];
    SDL_Rect winnerScreenPosition = {0, 0, WINDOWSIZE, WINDOWSIZE};
    // PLAY AGAIN SCREEN //
    SDL_Texture *mWaitingScreen = NULL;
    SDL_Rect gWaitingScreen[1];
    SDL_Rect waitingScreenPosition = {0, 0, WINDOWSIZE, WINDOWSIZE};

    // UDP //
    UDPsocket sd;
	IPaddress srvadd;
	UDPpacket *pSend, *pRecv;    //UDP packet to send and receive
    Data udpDataSend, udpDataRecv;  //UDP data to send and receive

    if (SDLNet_Init() < 0) 
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError()); 
		exit(EXIT_FAILURE); 
	}

    if(!(sd = SDLNet_UDP_Open(0)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
    /* Resolve server name  */
    if(SDLNet_ResolveHost(&srvadd, argv[1], port) == -1)
	{
		fprintf(stderr, "SDLNet_ResolveHost(192.0.0.1 2000): %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
   
    if(!((pSend = SDLNet_AllocPacket(sizeof(Data))) && (pRecv = SDLNet_AllocPacket(sizeof(Data))) ))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

    //Store current positions for comparison purposes later on
    int newXPos, newYPos, oldXPos, oldYPos;

    if(catNr == 1)
    {
        oldXPos = getCatPositionX(cats[0]);
        oldYPos = getCatPositionY(cats[0]);
    }
    else if(catNr == 2)
    {
        oldXPos = getCatPositionX(cats[1]);
        oldYPos = getCatPositionY(cats[1]);
    }
    else if(catNr == 3)
    {
        oldXPos = getCatPositionX(cats[2]);
        oldYPos = getCatPositionY(cats[2]);
    }
    else if(catNr == 4)
    {
        oldXPos = getCatPositionX(cats[3]);
        oldYPos = getCatPositionY(cats[3]);
    }
    
    //Let player with catNr 1 handle randomization of index for points
    if(catNr == 1)
    {
        index = rand()%NROFPOINTS; //Get random value from 0-19 
    }

    // SDL variables //
    SDL_Event e;
    SDL_Renderer *gRenderer = NULL;
    bool running = true;
    SDL_Window *gWindow = NULL;

    //Run game until player closes game window
    while(running)
    {
        switch(gameState)
        {
            case MENU:
            {
                while(menuChoice)
                {
                    menuChoice = menu(e);
                    gameState = PLAY;
                }
            }
            break;
            
            case PLAY:
            {
                if(init(&gRenderer,gWindow)) 
                {
                    printf("Worked\n");
                }

                //LOAD ALL IMAGES //
                loadMedia(gRenderer, &mTiles, gTiles, &mTree, gTreePic, &mBush, gBushPic, &mBerryBush, gBerryBushPic, &mPoint, gPointPic);
                loadCat(gRenderer, &mCat1, gCatSheet1, CAT1);
                loadCat(gRenderer, &mCat2, gCatSheet2, CAT2);
                loadCat(gRenderer, &mCat3, gCatSheet3, CAT3);
                loadCat(gRenderer, &mCat4, gCatSheet4, CAT4);
                loadCat(gRenderer, &mCaughtCat, gCaughtCatSheet, CAUGHTCAT);
                loadWinnerAndWaitingScreens(gRenderer, &mCat1WinnerScreen, gCat1WinnerScreen, CAT1_WINNERSCREEN);
                loadWinnerAndWaitingScreens(gRenderer, &mCat2WinnerScreen, gCat2WinnerScreen, CAT2_WINNERSCREEN);
                loadWinnerAndWaitingScreens(gRenderer, &mCat3WinnerScreen, gCat3WinnerScreen, CAT3_WINNERSCREEN);
                loadWinnerAndWaitingScreens(gRenderer, &mCat4WinnerScreen, gCat4WinnerScreen, CAT4_WINNERSCREEN);
                loadWinnerAndWaitingScreens(gRenderer, &mWaitingScreen, gWaitingScreen, PLAYAGAIN);
                
                while(running)
                {
                    //Check if any cat has collison with the chasing cat
                    catCollision(c1position, c2position, c3position, c4position,catNr, &moveLock, &caught, collisionCheck);
                    running = moveCat(catNr,gRenderer, e, cats, &flip1, &flip2, &flip3, &flip4, gPointPic, &c1position,&c2position,&c3position,&c4position, gWindow, &moveLock, &newPoint, &index, &cakeCounter, pointArray, &playAgain, &caughtCounter, collisionCheck);
                    
                    //If someone has pressed <PLAY AGAIN> store in a variable before it's reset
                    if(playAgain == 1)
                    {
                        playAgainCopy = 1;
                    }

                    //Set what data to send depending on your catNr
                    if(catNr == 1)
                    {
                        newXPos = c1position.x;
                        newYPos = c1position.y;
                        udpDataSend.frame = getCatFrame(cats[0]);
                        udpDataSend.flip = flip1;
                        udpDataSend.catNumber = catNr;
                    }
                    if(catNr == 2)
                    {
                        newXPos = c2position.x;
                        newYPos = c2position.y;
                        udpDataSend.frame = getCatFrame(cats[1]);
                        udpDataSend.flip = flip2;
                        udpDataSend.catNumber = catNr;
                    }
                    if(catNr == 3)
                    {
                        newXPos = c3position.x;
                        newYPos = c3position.y;
                        udpDataSend.frame = getCatFrame(cats[2]);
                        udpDataSend.flip = flip3;
                        udpDataSend.catNumber = catNr;
                    }
                    if(catNr == 4)
                    {
                        newXPos = c4position.x;
                        newYPos = c4position.y;
                        udpDataSend.frame = getCatFrame(cats[3]);
                        udpDataSend.flip = flip4;
                        udpDataSend.catNumber = catNr;
                    }
                    //If someone has taken a point..
                    if(newPoint == 1 && catNr != 1)
                    {
                        //Reset newPoint before checking for collison again
                        newPoint = 0;
                    }
                    if(newPoint == 1 && catNr == 1)
                    {
                        //Randomize index for next point
                        index = rand() % NROFPOINTS;
                        //Store newPoint in gojaSend and reset newPoint before checking for collison again
                        gojaSend = newPoint;
                        newPoint = 0;
                    }
                    //Check if any cat has collision with point
                    pointCollision(cats,c1position, c2position, c3position, c4position, pointPosition, catNr, &newPoint, pointArray, index);

                    //Check if any collecting cat has collected the max score 
                    if(((getCatPoints(cats[1])) == MAXSCORE) && (newPoint != MAXSCORE) && catNr == 2)
                    {
                        cakeCounter = (MAXSCORE+2);
                    }

                    if(((getCatPoints(cats[2])) == MAXSCORE) && (newPoint != MAXSCORE) && catNr == 3)
                    {
                        cakeCounter = (MAXSCORE+3);
                    }

                    if(((getCatPoints(cats[3])) == MAXSCORE) && (newPoint != MAXSCORE) && catNr == 4)
                    {
                        cakeCounter = (MAXSCORE+4);
                    }

                    //Send UDP data only if player has moved since last time, someone has taken a point, someone has pressed to play again and moveLock is disabled
                    if(oldXPos != newXPos || oldYPos != newYPos || gojaSend == 1|| playAgain == 1)
                    {
                        udpDataSend.x = newXPos;
                        udpDataSend.y = newYPos;
                        udpDataSend.newPoint = newPoint;
                        udpDataSend.playAgain = playAgain;
                        udpDataSend.indexForPoints = NROFPOINTS;
                      
                        if(catNr == 1)
                        {   
                            udpDataSend.caught = caught;
                            udpDataSend.indexForPoints = index;
                            gojaSend = 0;
                        }
                        else
                        {
                            udpDataSend.caught = 0;
                        }
                        if(cakeCounter >= MAXSCORE)
                        {
                            udpDataSend.newPoint = cakeCounter;
                        }

                        memcpy(pSend->data, &udpDataSend, sizeof(Data)+1);
                        pSend->len = sizeof(Data)+1;
                        pSend->address.host = srvadd.host;	/* Set the destination host */
                        pSend->address.port = srvadd.port;	/* And destination port */
                        SDLNet_UDP_Send(sd, -1, pSend);
                        oldXPos = newXPos;
                        oldYPos = newYPos;
                        playAgain = 0;
                    }  

                    //Enable movelock if someone has won
                    if(cakeCounter >= MAXSCORE)
                    {
                        moveLock = 1;
                    }

                    //Count a point for the chasing cat if it has caught another player
                    if(caught == 1 && catNr == 1)
                    {
                        caughtCounter++;
                        caught = 0;
                    }

                    //Check if there is a UDP packet to receive
                    if(SDLNet_UDP_Recv(sd, pRecv))
                    {
                        //Copy data from received packet into UDP data struct
                        memcpy(&udpDataRecv, (char * )pRecv->data, sizeof(Data));

                        //Increment newPoint if someone has taken a point to render out the another point at the next position
                        if(udpDataRecv.newPoint == 1)
                        {
                            newPoint = 1;
                        }

                        //If someone has won, lock movement 
                        if(udpDataRecv.newPoint >= MAXSCORE)
                        {
                            cakeCounter = udpDataRecv.newPoint;
                            moveLock = 1;
                        }

                        // RECEIVE UDP DATA DEPENDING ON WHICH CAT SENT IT //
                        if(udpDataRecv.catNumber == 1)
                        {
                            recUDPCat(cats[0], pRecv, udpDataRecv, &flip1, &pointPosition,&newPoint); 
                            index = udpDataRecv.indexForPoints;
                        }

                        if(udpDataRecv.catNumber == 2)
                        {
                            recUDPCat(cats[1], pRecv, udpDataRecv, &flip2, &pointPosition,&newPoint); 
                        }

                        if(udpDataRecv.catNumber == 3)
                        {
                            recUDPCat(cats[2], pRecv, udpDataRecv, &flip3, &pointPosition,&newPoint); 
                        }

                        if(udpDataRecv.catNumber == 4)
                        {
                            recUDPCat(cats[3], pRecv, udpDataRecv, &flip4, &pointPosition,&newPoint); 
                        }
                        
                        //Increment counter every time a player has pressed <PLAY AGAIN>
                        if(udpDataRecv.playAgain == 1)
                        {
                            playCounter++;
                        }
                        //Increment point counter for the chasing cat if it has caught another player
                        if(udpDataRecv.caught == 1)
                        {
                            caughtCounter++;
                            caught = 0; //Reset variable showing that chasing cat has caught a player
                        }
                    }
                    
                    if(playCounter == 3 && playAgainCopy == 1)
                    {
                        moveLock = 0;
                        playCounter = 0;
                        playAgainCopy = 0;
                        playAgain = 0;
                    }

                    //Set positions for the all cats and check collision with edges of game window
                    c1position.x = getCatPositionX(cats[0]);
                    c1position.y = getCatPositionY(cats[0]);
                    windowCollision(cats[0]);

                    c2position.x = getCatPositionX(cats[1]);
                    c2position.y = getCatPositionY(cats[1]);
                    windowCollision(cats[1]);

                    c3position.x = getCatPositionX(cats[2]);
                    c3position.y = getCatPositionY(cats[2]);
                    windowCollision(cats[2]); 

                    c4position.x = getCatPositionX(cats[3]);
                    c4position.y = getCatPositionY(cats[3]);
                    windowCollision(cats[3]);
        
                    // GAME RENDERER //
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    renderBackground(gRenderer, mTiles, gTiles); //world
                    renderBushes(gRenderer, mBush, gBushPic, mBerryBush, gBerryBushPic); //bushes
                    renderTrees(gRenderer, mTree, gTreePic); //trees
                    renderPoints(gRenderer, mPoint, gPointPic, pointArray, &index, &newPoint, &pointPosition); //points
                    SDL_RenderCopyEx(gRenderer, mCat1, &gCatSheet1[getCatFrame(cats[0])], &c1position ,0, NULL, flip1); //goja cat
                    
                    //If cat has been caught by the chasing cat render a dead cat in its position
                    if(collisionCheck[0] == 1)
                    {
                        SDL_RenderCopyEx(gRenderer, mCaughtCat, &gCaughtCatSheet[getCatFrame(cats[1])], &c2position ,0, NULL, flip2); 
                    }
                    else
                    {
                        SDL_RenderCopyEx(gRenderer, mCat2, &gCatSheet2[getCatFrame(cats[1])], &c2position ,0, NULL, flip2); //dad cat 
                    }
                    if(collisionCheck[1]==1)
                    {
                        SDL_RenderCopyEx(gRenderer, mCaughtCat, &gCaughtCatSheet[getCatFrame(cats[2])], &c3position ,0, NULL, flip3); //witch cat
                    }
                    else
                    {
                        SDL_RenderCopyEx(gRenderer, mCat3, &gCatSheet3[getCatFrame(cats[2])], &c3position ,0, NULL, flip3);
                    }
                    if(collisionCheck[2]==1)
                    {
                        SDL_RenderCopyEx(gRenderer, mCaughtCat, &gCaughtCatSheet[getCatFrame(cats[3])], &c4position ,0, NULL, flip4); //swim cat
                    }
                    else
                    {
                        SDL_RenderCopyEx(gRenderer, mCat4, &gCatSheet4[getCatFrame(cats[3])], &c4position ,0, NULL, flip4); 
                    }
                    
                    //Print winner screen for the cat that won
                    if(cakeCounter == (MAXSCORE+2))
                    {
                        SDL_RenderCopyEx(gRenderer, mCat2WinnerScreen, &gCat2WinnerScreen[0], &winnerScreenPosition, 0, NULL, SDL_FLIP_NONE); //dad win
                    }
                    if(cakeCounter == (MAXSCORE+3))
                    {
                        SDL_RenderCopyEx(gRenderer, mCat3WinnerScreen, &gCat3WinnerScreen[0], &winnerScreenPosition, 0, NULL, SDL_FLIP_NONE); //witch win
                    }
                    if(cakeCounter == (MAXSCORE+4))
                    {
                        SDL_RenderCopyEx(gRenderer, mCat4WinnerScreen, &gCat4WinnerScreen[0], &winnerScreenPosition, 0, NULL, SDL_FLIP_NONE); //swim win
                    }
                    if(caughtCounter == MAXSCORE_CHASINGCAT)
                    {
                        SDL_RenderCopyEx(gRenderer, mCat1WinnerScreen, &gCat1WinnerScreen[0], &winnerScreenPosition, 0, NULL, SDL_FLIP_NONE); //goja win
                    }

                    if (playAgainCopy==1)
                    {
                        //Show waiting screen until every player has pressed <PLAY AGAIN>
                        if(playCounter <= 3)  
                        {
                            SDL_RenderCopyEx(gRenderer, mWaitingScreen, &gWaitingScreen[0], &waitingScreenPosition, 0, NULL, SDL_FLIP_NONE);
               
                        }
                    }

                    
                    SDL_RenderPresent(gRenderer);
                }
                break;
            }
            break;
        }
    }
    return 0;
}

void catCollision(SDL_Rect c1position, SDL_Rect c2position, SDL_Rect c3position, SDL_Rect c4position, int catNr, int *pMoveLock, int *pCaught, int collisionCheck[])
{
    if(SDL_HasIntersection(&c1position, &c2position))
    {
        if(collisionCheck[0] == 0) //If cat hasn't been caught before
        {
            if(catNr == 2) //If I am the player who got caught..
            {
                *(pMoveLock) = 1; //Enable moveLock 
            }
            
            if(catNr == 1) //If I am the chasing cat..
            {
                *(pCaught) = 1; //Acknowledge that a player has been caught
            }
            collisionCheck[0] = 1; //Set to one to show that this cat has been caught
        }

    }

    if(SDL_HasIntersection(&c1position, &c3position))
    {
        if(collisionCheck[1] == 0)
        {
            if(catNr == 3)
            {
            *(pMoveLock) = 1; 
            }
            
            if (catNr == 1)
            {
                *(pCaught) = 1;
            }

            collisionCheck[1] = 1;
        }
    }

    if(SDL_HasIntersection(&c1position, &c4position))
    {
        if(collisionCheck[2] == 0)
        {
            if(catNr == 4)
            {
            *(pMoveLock) = 1; 
            }
            
            if (catNr == 1)
            {
                *(pCaught) = 1;
            }

            collisionCheck[2] = 1;
        }
    }
}

int menu(SDL_Event e)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize\n");
    }

    SDL_Window *window = SDL_CreateWindow("STRAWBERRY CHASECAKE ฅ^•ﻌ•^ฅ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWSIZE, WINDOWSIZE, 0);

    if(!window)
    {
        printf("Failed to create window\n");
    }

    SDL_Surface *windowSurface = SDL_GetWindowSurface(window);

    if(!windowSurface)
    {
        printf("Failed to get the surface from the window\n");
    }

    SDL_Surface *image = IMG_Load(MENU_SCREEN);

    if(!image)
    {
        printf("Failed to load image\n");
    }

    bool keepWindowOpen = true;
    while(keepWindowOpen)
    {
        while(SDL_PollEvent(&e) > 0)
        {
            if (e.type==SDL_QUIT)
            {
                keepWindowOpen = false;
                SDL_DestroyWindow(window);
                break;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                //If player presses <PLAY>
                if(e.button.x > 250 && e.button.x < 450 && e.button.y < 220 && e.button.y > 160)
                {
                    keepWindowOpen = false;
                    SDL_DestroyWindow(window);
                    return 0;
                }
                //If player presses <QUIT>
                else if(e.button.x > 250 && e.button.x < 450 && e.button.y < 390 && e.button.y > 290)
                {
                    printf("quit\n");
                    SDL_DestroyWindow(window);
                    SDL_VideoQuit();
                    SDL_Quit();
                    exit(0); //Terminate program
                }
            }

            SDL_BlitSurface(image, NULL, windowSurface, NULL);
            SDL_UpdateWindowSurface(window);
        }
    }
    
    return 1;
}

void renderPoints(SDL_Renderer *gRenderer, SDL_Texture *mPoint, SDL_Rect gPointPic[], int positionArray[][2], int *pIndex, int *pNewPoint, SDL_Rect pointPosition[])
{
    if(*(pIndex) <= NROFPOINTS-1)
    {
        pointPosition->x = positionArray[(*pIndex)][0]; //get x position for current point
        pointPosition->y = positionArray[(*pIndex)][1]; //get y position for current point
        pointPosition->h = getPointHeight();
        pointPosition->w = getPointWidth();

        if(pointPosition->x > 0 && pointPosition->y > 0 && *pNewPoint!=MAXSCORE)
        {
            SDL_RenderCopyEx(gRenderer, mPoint, &gPointPic[0], pointPosition, 0, NULL, SDL_FLIP_NONE);
            getPointPositionArray(positionArray);
        }
    }

    return;
}

void recUDPCat(Cat c, UDPpacket *packet, Data udpData, SDL_RendererFlip *flip, SDL_Rect *pointPosition, int *pNewPoint) 
{
    memcpy(&udpData, (char * ) packet->data, sizeof(Data));
    setCatPositionX(c, udpData.x);
    setCatPositionY(c, udpData.y);
    setCatFrame(c, udpData.frame);
    (*flip) = udpData.flip;
    printf("Catnr: %d - UDP Packet incoming %d %d %d %d %d %d %d %d\n", udpData.catNumber, udpData.x, udpData.y, udpData.frame, udpData.flip, udpData.playAgain, udpData.newPoint, udpData.caught, udpData.indexForPoints);
}

void setAnimationFrame(Cat c, SDL_RendererFlip *flip, int direction)
{
    //Sets correct image depending on which direction player is moving
    switch(direction)
    {
        case UP:
            (*flip) = SDL_FLIP_NONE;
            if(getCatFrame(c) == 4)
                setCatFrame(c, 5);
            else
                setCatFrame(c, 4);
            break;

        case DOWN: 
            (*flip) = SDL_FLIP_NONE;
            if(getCatFrame(c) == 0)
                setCatFrame(c, 1);
            else
                setCatFrame(c, 0);
            break;

        case LEFT: 
            (*flip) = SDL_FLIP_HORIZONTAL;
            if(getCatFrame(c) == 2)
                setCatFrame(c, 3);
            else
                setCatFrame(c, 2);
            break;
        case RIGHT:
            (*flip) = SDL_FLIP_NONE;
            if(getCatFrame(c) == 2)
                setCatFrame(c, 3);
            else
                setCatFrame(c, 2);
            break;
        default:
            break;
    }
}

int moveCat(int catNr, SDL_Renderer *gRenderer, SDL_Event e, Cat cats[], SDL_RendererFlip *flip1,SDL_RendererFlip *flip2,SDL_RendererFlip *flip3,SDL_RendererFlip *flip4, SDL_Rect gPointPic[],SDL_Rect *c1position, SDL_Rect *c2position,SDL_Rect *c3position, SDL_Rect *c4position, SDL_Window *gWindow, int *pMoveLock, int *pNewPoint, int *pIndex, int*pCakeCounter,int pointArray[][2],int *pPlayAgain, int *pCaughtCounter, int collisionCheck[])
{
    while(SDL_PollEvent(&e)) 
    {
        if(e.type == SDL_QUIT) 
        {
            return false;
        }
        //Moving is only allowed if moveLock is disabled
        else if(e.type == SDL_KEYDOWN && !(*pMoveLock))
        {
            switch(e.key.keysym.sym )
            {
                case SDLK_UP:
                    moveCatsUp(catNr, cats[0], cats[1], cats[2], cats[3], flip1, flip2, flip3, flip4);
                    break;
                case SDLK_DOWN:
                    moveCatsDown(catNr, cats[0], cats[1], cats[2], cats[3], flip1, flip2, flip3, flip4);
                    break;
                case SDLK_LEFT:
                    moveCatsLeft(catNr, cats[0], cats[1], cats[2], cats[3], flip1, flip2, flip3, flip4);
                    break;
                case SDLK_RIGHT:
                    moveCatsRight(catNr, cats[0], cats[1], cats[2], cats[3], flip1, flip2, flip3, flip4);
                    break;
            }
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            //If player presses <PLAY AGAIN> and the game round has finished
            if(e.button.x>115 && e.button.x<544 && e.button.y<544 && e.button.y >480 && (*pCakeCounter) >= MAXSCORE || (*pCaughtCounter) == MAXSCORE_CHASINGCAT)
            {
                //Reset starting positions and needed variables
                playAgain(cats,c1position,c2position,c3position,c4position,flip1,flip2,flip3,flip4, pNewPoint,pIndex,pMoveLock,pCakeCounter,pPlayAgain,pCaughtCounter, collisionCheck,catNr);
                getPointPositionArray(pointArray);
            }
        }
    } 

    return true;
}

void resetCollisionCheck(int collisionCheck[])
{
    for(int i = 0; i < NROFCATS-1; i++)
    {
        collisionCheck[i] = 0;
    }  
}

void playAgain(Cat cats[], SDL_Rect *c1position, SDL_Rect *c2position, SDL_Rect *c3position, SDL_Rect *c4position, SDL_RendererFlip *flip1, SDL_RendererFlip *flip2, SDL_RendererFlip *flip3,SDL_RendererFlip *flip4, int *pNewPoint, int *pIndex, int *pMoveLock, int *pCakeCounter, int *pPlayAgain, int *pCaughtCounter, int collisionCheck[], int catNr)
{
    *(pNewPoint) = 0;

    if(catNr == 1)
    {
        *(pIndex) = rand()%NROFPOINTS;
    }

    *(pCakeCounter) = 0;
    *(pPlayAgain) = 1;
    *(pCaughtCounter) = 0;
    resetCollisionCheck(collisionCheck);

    *(flip1) = SDL_FLIP_NONE;
    setCatPositionX(cats[0], 32);
    setCatPositionY(cats[0], 576);
    setCatFrame(cats[0], STARTFRAME);
    setCatPoints(cats[0], 0);
    c1position->x=getCatPositionX(cats[0]);
    c1position->y=getCatPositionY(cats[0]);
    c1position->h=getCatHeight();
    c1position->w=getCatWidth();

    *(flip2) = SDL_FLIP_NONE;
    setCatPositionX(cats[1], 576);
    setCatPositionY(cats[1], 25);
    setCatFrame(cats[1], STARTFRAME);
    setCatPoints(cats[1], 0);
    c2position->x=getCatPositionX(cats[1]);
    c2position->y=getCatPositionY(cats[1]);
    c2position->h=getCatHeight();
    c2position->w=getCatWidth();

    *(flip3) = SDL_FLIP_NONE;
    setCatPositionX(cats[2], 576);
    setCatPositionY(cats[2], 576);
    setCatFrame(cats[2], STARTFRAME);
    setCatPoints(cats[2], 0);
    c3position->x=getCatPositionX(cats[2]);
    c3position->y=getCatPositionY(cats[2]);
    c3position->h=getCatHeight();
    c3position->w=getCatWidth();

    *(flip4) = SDL_FLIP_NONE;
    setCatPositionX(cats[3], 32);
    setCatPositionY(cats[3], 32);
    setCatFrame(cats[3], STARTFRAME);
    setCatPoints(cats[3], 0);
    c4position->x=getCatPositionX(cats[3]);
    c4position->y=getCatPositionY(cats[3]);
    c4position->h=getCatHeight();
    c4position->w=getCatWidth();
}

void moveCatsLeft(int catNr,Cat c1, Cat c2, Cat c3, Cat c4,SDL_RendererFlip *flip1,SDL_RendererFlip *flip2,SDL_RendererFlip *flip3,SDL_RendererFlip *flip4)
{
    if(catNr == 1)
    {
        setCatPositionX(c1,(getCatPositionX(c1)-(SPEED+1)));
        setAnimationFrame(c1, flip1, LEFT);
    }
    else if(catNr == 2)
    {
        setCatPositionX(c2,(getCatPositionX(c2)-SPEED));
        setAnimationFrame(c2, flip2, LEFT);
    }
    else if (catNr == 3)
    {
        setCatPositionX(c3,(getCatPositionX(c3)-SPEED));
        setAnimationFrame(c3, flip3, LEFT);
    }
    else if (catNr == 4)
    {
        setCatPositionX(c4,(getCatPositionX(c4)-SPEED));
        setAnimationFrame(c4, flip4, LEFT);
    }
}

void moveCatsRight(int catNr,Cat c1, Cat c2, Cat c3, Cat c4,SDL_RendererFlip *flip1,SDL_RendererFlip *flip2,SDL_RendererFlip *flip3,SDL_RendererFlip *flip4)
{
    if(catNr == 1)
    {
        setCatPositionX(c1,(getCatPositionX(c1)+(SPEED+1)));
        setAnimationFrame(c1, flip1, RIGHT);
    }
    else if(catNr == 2)
    {
        setCatPositionX(c2,(getCatPositionX(c2)+SPEED));
        setAnimationFrame(c2, flip2, RIGHT);
    }
    else if(catNr == 3)
    {
        setCatPositionX(c3,(getCatPositionX(c3)+SPEED));
        setAnimationFrame(c3, flip3, RIGHT);
    }
    else if(catNr == 4)
    {
        setCatPositionX(c4,(getCatPositionX(c4)+SPEED));
        setAnimationFrame(c4, flip4, RIGHT);
    }
}

void moveCatsDown(int catNr,Cat c1, Cat c2, Cat c3, Cat c4,SDL_RendererFlip *flip1,SDL_RendererFlip *flip2,SDL_RendererFlip *flip3,SDL_RendererFlip *flip4)
{
    if(catNr == 1)
    {
        setCatPositionY(c1,(getCatPositionY(c1)+(SPEED+1)));
        setAnimationFrame(c1, flip1, DOWN);
    }
    else if(catNr == 2)
    {
        setCatPositionY(c2,(getCatPositionY(c2)+SPEED));
        setAnimationFrame(c2, flip2, DOWN);
    }
    else if(catNr == 3)
    {
        setCatPositionY(c3,(getCatPositionY(c3)+SPEED));
        setAnimationFrame(c3, flip3, DOWN);
    }
    else if(catNr == 4)
    {
        setCatPositionY(c4,(getCatPositionY(c4)+SPEED));
        setAnimationFrame(c4, flip4, DOWN);
    }
}

void moveCatsUp(int catNr,Cat c1, Cat c2, Cat c3, Cat c4,SDL_RendererFlip *flip1,SDL_RendererFlip *flip2,SDL_RendererFlip *flip3,SDL_RendererFlip *flip4)
{
    if (catNr == 1)
    {
        setCatPositionY(c1,(getCatPositionY(c1)-(SPEED+1)));
        setAnimationFrame(c1, flip1, UP);
    }
    else if(catNr == 2)
    {
        setCatPositionY(c2,(getCatPositionY(c2)-SPEED));
        setAnimationFrame(c2, flip2, UP);
    }
    else if(catNr == 3)
    {
        setCatPositionY(c3,(getCatPositionY(c3)-SPEED));
        setAnimationFrame(c3, flip3, UP);
    }
    else if(catNr == 4)
    {
        setCatPositionY(c4,(getCatPositionY(c4)-SPEED));
        setAnimationFrame(c4, flip4, UP);
    }
}

void renderBackground(SDL_Renderer *gRenderer, SDL_Texture *mTiles, SDL_Rect gTiles[])
{
    SDL_Rect position;
    position.y = 0;
    position.x = 0;
    position.h = getTileHeight();
    position.w = getTileWidth();
    
    for (int i = 0; i < getTileColumns(); i++) 
    {
        for (int j = 0; j < getTileRows(); j++) 
        {
            position.y = i*getTileHeight();
            position.x = j*getTileWidth();
            SDL_RenderCopyEx(gRenderer, mTiles, &gTiles[getTileGrid(i,j)],&position , 0, NULL, SDL_FLIP_NONE);
        }
    }
}

void renderTrees(SDL_Renderer *gRenderer, SDL_Texture *mTree, SDL_Rect gTreePic[])
{
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    position.h = getTreeHeight();
    position.w = getTreeWidth();

    for(int i = 0; i < getNrOfTrees(); i++)
    {
        position.x = getTreeX(i);
        position.y = getTreeY(i);
        SDL_RenderCopyEx(gRenderer, mTree, &gTreePic[0], &position, 0, NULL, SDL_FLIP_NONE);
    }

    return;
}

void renderBushes(SDL_Renderer *gRenderer, SDL_Texture *mBush, SDL_Rect gBushPic[], SDL_Texture *mBerryBush, SDL_Rect gBerryBushPic[])
{
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    position.h = getBushHeight();
    position.w = getBushWidth();
    int change = 0; // Every other bush is a green bush
    
    for(int i = 0; i < getNrOfBushes(); i++)
    {
        position.x = getBushX(i);
        position.y = getBushY(i);
        
        if(change == 0)
        {
            SDL_RenderCopyEx(gRenderer, mBush, &gBushPic[0], &position, 0, NULL, SDL_FLIP_NONE);
            change++;
        }
        else
        {
            SDL_RenderCopyEx(gRenderer, mBerryBush, &gBerryBushPic[0], &position, 0, NULL, SDL_FLIP_NONE);
            change = 0;
        }
    }

    return;
}

void loadMedia(SDL_Renderer *gRenderer, SDL_Texture **mTiles, SDL_Rect gTiles[], SDL_Texture **mTree, SDL_Rect gTreePic[], SDL_Texture **mBush, SDL_Rect gBushPic[],SDL_Texture **mBerryBush, SDL_Rect gBerryBushPic[], SDL_Texture **mPoint, SDL_Rect gPointPic[])
{
    // POINT //
    SDL_Surface* gPointSurface = IMG_Load(POINT); //Loads image for points
    *mPoint = SDL_CreateTextureFromSurface(gRenderer, gPointSurface);
    gPointPic[ 0 ].x = 0;
    gPointPic[ 0 ].y = 0;
    gPointPic[ 0 ].w = getPointWidth();
    gPointPic[ 0 ].h = getPointHeight();

    // TREE //
    SDL_Surface* gTreeSurface = IMG_Load(PINKTREE); //Loads image of tree
    *mTree = SDL_CreateTextureFromSurface(gRenderer, gTreeSurface);
    gTreePic[ 0 ].x = 0;
    gTreePic[ 0 ].y = 0;
    gTreePic[ 0 ].w = getTreeWidth();
    gTreePic[ 0 ].h = getTreeHeight(); 
    
    // TILES //
    SDL_Surface* gTilesSurface = IMG_Load(TILES); //Loads image of tile set
    *mTiles = SDL_CreateTextureFromSurface(gRenderer, gTilesSurface);
    for (int i = 0; i < 24; i++) 
    {
        gTiles[i].x = i*getTileWidth();
        gTiles[i].y = 0;
        gTiles[i].w = getTileWidth();
        gTiles[i].h = getTileHeight();
    }

    // GREEN BUSH //
    SDL_Surface* gBushSurface1 = IMG_Load(BUSH); //Loads image of green bush
    *mBush = SDL_CreateTextureFromSurface(gRenderer, gBushSurface1);
    gBushPic[ 0 ].x = 0;
    gBushPic[ 0 ].y = 0;
    gBushPic[ 0 ].w = getBushWidth();
    gBushPic[ 0 ].h = getBushHeight(); 

    // BERRY BUSH //
    SDL_Surface* gBushSurface2 = IMG_Load(BERRYBUSH); //Loads image of bush with berries
    *mBerryBush = SDL_CreateTextureFromSurface(gRenderer, gBushSurface2);
    gBerryBushPic[ 0 ].x = 0;
    gBerryBushPic[ 0 ].y = 0;
    gBerryBushPic[ 0 ].w = getBushWidth();
    gBerryBushPic[ 0 ].h = getBushHeight(); 
}

void loadWinnerAndWaitingScreens(SDL_Renderer *gRenderer, SDL_Texture **mScreen, SDL_Rect gScreen[], char screen[])
{
    gScreen[ 0 ].x = 0;
    gScreen[ 0 ].y = 0;
    gScreen[ 0 ].w = WINDOWSIZE;
    gScreen[ 0 ].h = WINDOWSIZE;

    SDL_Surface* gScreenSurface = IMG_Load(screen);
    *mScreen = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

    if(!gScreenSurface)
    {
        printf("Winner/Waiting screen failed to load\n");
    }
}

void loadCat(SDL_Renderer *gRenderer, SDL_Texture **mCharacter, SDL_Rect gArray[], char bmp[])
{
    SDL_Surface* gCharacterSurface = IMG_Load(bmp); //Loads a sprite sheet
    *mCharacter = SDL_CreateTextureFromSurface(gRenderer, gCharacterSurface);
    setSpriteClips(gArray); //Sets frames at right position in array
}

void setSpriteClips(SDL_Rect gArray[])
{
    int x = 0;

    for(int i = 0; i < SPRITEFRAMES; i++)
    {
        gArray[i].x = x;
        gArray[i].y = 0;
        gArray[i].w = getCatWidth();
        gArray[i].h = getCatHeight();
        x += getCatWidth();
    }
}

void windowCollision(Cat c)
{
    if(getCatPositionX(c) < 32 )        //LEFT SIDE
    {
        setCatPositionX(c, 32);
    }

    else if(getCatPositionX(c) > 576)   //RIGHT SIDE 
    {
        setCatPositionX(c, 576);
    }

    if(getCatPositionY(c) > 565)        //LOWER SIDE
    {
        setCatPositionY(c, 565);
    }

    else if(getCatPositionY(c) < 20)    //UPPER SIDE
    {
        setCatPositionY(c, 20);
    } 
}

void pointCollision(Cat cats[], SDL_Rect c1position, SDL_Rect c2position, SDL_Rect c3position, SDL_Rect c4position, SDL_Rect pointPosition, int catNr, int *pNewPoint, int pointArray[][2], int index)
{
    switch (catNr)
    {
        case 1: 
            if(SDL_HasIntersection(&c1position, &pointPosition))
            {
                printf("collision\n");
                pointArray[index][0]=0;
                pointArray[index][1]=0;
                (*pNewPoint) = 1;
            }
            break;
        case 2:
            if(SDL_HasIntersection(&c2position, &pointPosition))
            {
                printf("collision\n");
                pointArray[index][0]=0;
                pointArray[index][1]=0;
                (*pNewPoint) = 1;
                setCatPoints(cats[1], getCatPoints(cats[1])+1);
                printf("Point for cat #%d: %d\n", catNr, getCatPoints(cats[1]));
            }
            break;
        case 3:
            if(SDL_HasIntersection(&c3position, &pointPosition))
            {
                printf("collision\n");
                pointArray[index][0]=0;
                pointArray[index][1]=0;
                (*pNewPoint) = 1;
                setCatPoints(cats[2], getCatPoints(cats[2])+1);
                printf("Point for cat #%d: %d\n", catNr, getCatPoints(cats[2]));
            }
            break;
        case 4:
            if(SDL_HasIntersection(&c4position, &pointPosition))
            {
                printf("collision\n");
                pointArray[index][0]=0;
                pointArray[index][1]=0;
                (*pNewPoint) = 1;
                setCatPoints(cats[3], getCatPoints(cats[3])+1);
                printf("Point for cat #%d: %d\n", catNr, getCatPoints(cats[3]));
            }
            break;
    }
}

bool init(SDL_Renderer **gRenderer, SDL_Window *gWindow)
{
    bool test = true;
    SDL_Init(SDL_INIT_VIDEO);

    gWindow = SDL_CreateWindow("STRAWBERRY CHASECAKE ฅ^•ﻌ•^ฅ", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, WINDOWSIZE, WINDOWSIZE, SDL_WINDOW_SHOWN);

    if(gWindow == NULL)
    {
        printf("Didn't work\n");
        test = false;
    }

    *gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);

    if(*gRenderer == NULL)
    {
        printf("Didn't work\n");
        test = false;
    }

    return test;
}