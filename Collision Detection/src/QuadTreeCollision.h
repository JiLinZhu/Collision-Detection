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
	double lowBoundX;
	double lowBoundY;
	double upBoundX;
	double upBoundY;
	Shape *objects;
	struct QuadTreeT *nodes;
}QuadTree;


QuadTree quadTreeCreate( int level, int lowBoundX, int lowBoundY, int upBoundX, int upBoundY );

void quadTreeClear( QuadTree q );

void split( QuadTree q );

int getQuad( Shape *s, QuadTree q );

#endif /* QUADTREECOLLISION_H_ */


