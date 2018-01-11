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

QuadTree quadTreeCreate( int level, int size, double lowBoundX, double lowBoundY, double upBoundX, double upBoundY ){
	Shape s = { 0, NULL, NULL };
	QuadTree a = { 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL };
	Shape *objects = malloc( sizeof(Shape) * 10 ); assert(objects);
	QuadTree *nodes = malloc( sizeof(QuadTree) * 4); assert(nodes);
	for( int i = 0; i < 10; i++ ) objects[i] = s;
	for( int i = 0; i < 4; i++ ) nodes[i] = a;
	QuadTree q = {10, 5, level, size, lowBoundX, lowBoundY, upBoundX, upBoundY, objects, nodes};
	return q;
}

double getMinMaxX ( Shape *s, int minMax ){
	double curX;
	double minMaxX = s->points[0].x * minMax;
	for( int i = 1; i < s->numPoints; i++ ) {
		curX = s->points[i].x * minMax;
		if ( curX > minMaxX ) minMaxX = curX;
	}
	return fabs(minMaxX);
}

double getMinMaxY ( Shape *s, int minMax ){
	double curY;
	double minMaxY = s->points[0].y * minMax;
	for( int i = 1; i < s->numPoints; i++ ) {
		curY = s->points[i].y * minMax;
		if ( curY > minMaxY ) minMaxY = curY;
	}
	return fabs(minMaxY);
}

void clear( QuadTree *q ){
	q->curObj = 0;
	for( int i = 0; i < 4; i++ ) {
		if ( q->nodes[i].maxLvl != 0 ) clear(&q->nodes[i]);
		q->nodes[i].maxLvl = 0;
	}

	for( int i = 0; i < q->curObj; i++ ) q->objects[i].numPoints = 0;
}

void split( QuadTree *q ){
	double midX = q->lowBoundX + (q->upBoundX-q->lowBoundX)/2;
	double midY = q->lowBoundY + (q->upBoundY-q->lowBoundY)/2;

	q->nodes[0] = quadTreeCreate( q->curLvl + 1, 0, q->lowBoundX, q->upBoundY, midX, midY );
	q->nodes[1] = quadTreeCreate( q->curLvl + 1, 0, midX, q->upBoundY, q->upBoundX, midY );
	q->nodes[2] = quadTreeCreate( q->curLvl + 1, 0, q->lowBoundX, midY, midX, q->lowBoundY );
	q->nodes[3] = quadTreeCreate( q->curLvl + 1, 0, midX, midY, q->upBoundX, q->lowBoundY );
}

int getQuad( Shape *s, QuadTree q ){
	bool leftHalf = false, rightHalf = false;
	double minX = getMinMaxX( s, -1 ), maxX = getMinMaxX( s, 1 );
	double minY = getMinMaxY( s, -1 ), maxY = getMinMaxY( s, 1 );
	double midBoundX = q.lowBoundX + (q.upBoundX - q.lowBoundX)/2;
	double midBoundY = q.lowBoundY + (q.upBoundY - q.lowBoundY)/2;

	if ( minX >= q.lowBoundX && maxX <= midBoundX ) leftHalf = true;
	else if ( minX >= midBoundX && maxX <= q.upBoundX ) rightHalf = true;
	else return -1;

	if ( minY >= q.lowBoundY && maxY <= midBoundY ) {
		if ( leftHalf ) return 2;
		else return 3;
	} else if ( minY >= midBoundY && maxY <= q.upBoundY ) {
		if ( leftHalf ) return 0;
		else return 1;
	} else return -1;
}

void insertObject( Shape *s, QuadTree *q ){
	if( q->nodes[0].maxLvl != 0 ){
		int index = getQuad( s, *q );

		if ( index != -1 ) {
			insertObject( s, &q->nodes[index] );
			return;
		}
	}

	q->objects[q->curObj++] = *s;

	if( q->curObj > q->maxObj && q->curLvl < q->maxLvl ) {
		if ( q->nodes[0].maxLvl == 0 ) split( q );
		for( int i = 0; i < q->maxObj; i++ ) {
			int index = getQuad( &q->objects[i], *q );
			if ( index != -1 ) {
				insertObject( &q->objects[i], &q->nodes[index] );
				q->curObj--;
				q->objects[i].numPoints = 0;
			}
		}
		resetObjectsPosition( q );
	}
}

void resetObjectsPosition( QuadTree *q ){
	int counter = 0;
	for ( int i = 0; i < q->maxObj; i++ ) if( q->objects[i].numPoints != 0 ) q->objects[counter++] = q->objects[i];
	for ( int i = counter; i < q->maxLvl; i++ ) q->objects[i].numPoints = 0;
}

Shape *retreiveCollision( Shape *s, QuadTree q ){
	int index = getQuad( s, q );
	if ( index != -1 && q.nodes[0].maxLvl != 0 ) return retreiveCollision( s, q.nodes[index] );
	else return q.objects;
}

//When checking for collision, ensure that q->objects[i].numPoints != 0;
