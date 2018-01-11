/*
 * QuadTreeCollision.h
 *
 *  Created on: Dec 30, 2017
 *      Author: jilin
 */

#ifndef QUADTREECOLLISION_H_
#define QUADTREECOLLISION_H_


typedef struct QuadTreeT{
	int maxObj; //10;
	int maxLvl; //5;
	int curLvl;
	int curObj;
	double lowBoundX;
	double lowBoundY;
	double upBoundX;
	double upBoundY;
	Shape *objects;
	struct QuadTreeT *nodes;
}QuadTree;


/*
 * QuadTreeCollision.c
 *
 *  Created on: Dec 30, 2017
 *      Author: jilin
 */


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Vector.h"
#include "QuadTreeCollision.h"

QuadTree quadTreeCreate( int level, int size, double lowBoundX, double lowBoundY, double upBoundX, double upBoundY );

double getMinMaxX ( Shape *s, int minMax );

double getMinMaxY ( Shape *s, int minMax );

void clear( QuadTree *q );

void split( QuadTree *q );

int getQuad( Shape *s, QuadTree q );

void insertObject( Shape *s, QuadTree *q );

void resetObjectsPosition( QuadTree *q );

Shape *retreiveCollision( Shape *s, QuadTree q );

#endif /* QUADTREECOLLISION_H_ */


