/*
 * SATCollision.c
 *
 *  Created on: Dec 23, 2017
 *      Author: jilin
 */

//Collision Detection Done with Separating Axis Theorem

#include <math.h>
#include <stdbool.h>
#include "Vector.h"

double findMinMaxProj( Shape *x, Vector axis, int minMax ){ //-1 is min, 1 is max
	double curProj;
	double minMaxProj = proj( x->points[0], axis ) * minMax;
	for( int i = 1; i < x->numPoints; i++ ){
		curProj = proj( x->points[i], axis ) * minMax;
		if ( curProj > minMaxProj ) minMaxProj = curProj;
	}
	return fabs(minMaxProj);
}

bool collisionDetectedSAT( Shape *x, Shape *y ){
	double minProjX, maxProjX, minProjY, maxProjY;
	for( int i = 0; i < x->numPoints; i++ ) {
		minProjX = findMinMaxProj( x, x->normals[i], -1 );
		maxProjX = findMinMaxProj( x, x->normals[i], 1 );
		minProjY = findMinMaxProj( y, x->normals[i], -1 );
		maxProjY = findMinMaxProj( y, x->normals[i], 1 );
		if ( minProjX > maxProjY || minProjY > maxProjX ) return false;
	}

	for( int i = 0; i < y->numPoints; i++ ) {
		minProjX = findMinMaxProj( x, y->normals[i], -1 );
		maxProjX = findMinMaxProj( x, y->normals[i], 1 );
		minProjY = findMinMaxProj( y, y->normals[i], -1 );
		maxProjY = findMinMaxProj( y, y->normals[i], 1 );
		if ( minProjX > maxProjY || minProjY > maxProjX ) return false;
	}
	return true;
}


