#ifndef cat_h
#define cat_h

#include <stdio.h>

typedef struct Cat_type *Cat;

int getCatPositionX(Cat c);
int getCatPositionY(Cat c);
Cat createCat(int x, int y, int frame, int points);
void setCatPositionY(Cat c, int y);
void setCatPositionX(Cat c, int x);
int getCatWidth();
int getCatHeight();
int getCatFrame(Cat c);
void setCatFrame(Cat c, int frame);
void setCatPoints(Cat c, int points);
int getCatPoints(Cat c);

#endif /* Cat_h */