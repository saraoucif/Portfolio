#include <stdlib.h>
#include "cat.h"
 
#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int CAT_WIDTH = 32;
PRIVATE int CAT_HEIGHT = 32;

struct Cat_type{
    int CAT_POSITION_X;
    int CAT_POSITION_Y;
    int CAT_FRAME;
    int CAT_POINTS;
};

PUBLIC Cat createCat(int x, int y, int frame, int points){
    Cat c = malloc(sizeof(struct Cat_type));
    c->CAT_POSITION_Y = y;
    c->CAT_POSITION_X = x;
    c->CAT_FRAME = frame;
    c->CAT_POINTS = points;
    return c;
}

PUBLIC void setCatPositionY(Cat c, int y){
    c->CAT_POSITION_Y = y;
}

PUBLIC void setCatPositionX(Cat c, int x){
    c->CAT_POSITION_X = x;
}

PUBLIC int getCatPositionX(Cat c){
    return c->CAT_POSITION_X;
}

PUBLIC int getCatPositionY(Cat c){
    return c->CAT_POSITION_Y;
}

PUBLIC int getCatWidth(){
    return CAT_WIDTH;
}

PUBLIC int getCatHeight(){
    return CAT_HEIGHT;
}

PUBLIC int getCatFrame(Cat c){
    return c->CAT_FRAME;
}

PUBLIC void setCatFrame(Cat c, int frame){
    c->CAT_FRAME=frame;
}

PUBLIC void setCatPoints(Cat c, int points){
    c->CAT_POINTS=points;
}

PUBLIC int getCatPoints(Cat c){
    return c->CAT_POINTS;
}