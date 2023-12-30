#ifndef world_h
#define world_h

#include <stdio.h>

int getTileRows();
int getTileColumns();
int getTileWidth();
int getTileHeight();
int getTileGrid(int x, int y);

int getTreeWidth();
int getTreeHeight();
int getNrOfTrees();
int getTreeX(int i);
int getTreeY(int i);

int getBushWidth();
int getBushHeight();
int getNrOfBushes();
int getBushX(int i);
int getBushY(int i);

#endif /* world_h */
