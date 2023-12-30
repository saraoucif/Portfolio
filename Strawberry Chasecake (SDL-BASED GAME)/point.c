#include <stdio.h>
#include "point.h"

#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int POINT_WIDTH = 32;
PRIVATE int POINT_HEIGHT = 32;

PUBLIC int getPointWidth(){
    return POINT_WIDTH;
}

PUBLIC int getPointHeight(){
    return POINT_HEIGHT;
}

PRIVATE int NR_OF_POINTS = 20;

PUBLIC int getNrOfPoints(){
    return NR_OF_POINTS;
}

PRIVATE int pointCoordinates[20][2] = {
    {64, 96},
    {32, 256},
    {32, 448},
    {64, 576},
    {128, 96},
    {128, 384},
    {224, 288},
    {256, 160},
    {256, 512},
    {288, 32},
    {320, 384},
    {320, 576},
    {352, 512},
    {384, 224},
    {448, 96},
    {480, 320},
    {544, 32},
    {544, 416},
    {576, 224},
    {576, 514},
};

PUBLIC int getPointX(int i){
    return pointCoordinates[i][0];
}

PUBLIC int getPointY(int i){
    return pointCoordinates[i][1];
}

PUBLIC void getPointPositionArray(int pointArray[][2]){
    for (int i = 0; i < getNrOfPoints(); i++)
    {
        pointArray[i][0]=getPointX(i);
        pointArray[i][1]=getPointY(i);
    }
}